#include "dbgdetector.h"

using namespace std;
#define TOTALVMRESERVE 0x00100000

void DBGdetector::detector(vector<HANDLE> handles){
	vector<int> check = detect_debugger(handles);

	bool none = true;
	int count = 0;
	for (int i = 0; i < check.size(); i++){
		if (handles[i] == this_process){
			check[i] = 0;
		}
		if (check[i] != 0){
			int pid = GetProcessId(handles[i]);
			int check_pid = 0;
			cout << "debugger detected at " << pid << ", " << check[i] << " tests" << endl;
			none = false;
			count++;
		}
	}

	kill_processes(handles, check);

	cout << check.size() << " , " << count << endl;
	if (none)
		cout << "no debugger detected." << endl;
}

vector<int> DBGdetector::detect_debugger(vector<HANDLE> handles){
	vector<int> indecies;
	indecies.assign(handles.size(), 0);

	for (int i = 0; i < handles.size(); i++){
		if (detect_api(handles[i])){
			indecies[i]++;
		}
	}
	for (int i = 0; i < handles.size(); i++){
		string bytes = get_mem(handles[i]);
		if (bytes != ""){
			if (detect_flags(bytes)){
				cout << indecies[i]++;
			}
		}
	}
	for (int i = 0; i < handles.size(); i++){
		string bytes = get_mem(handles[i]);
		if (bytes != ""){
			if (detect_exception(bytes)){
				cout << indecies[i]++;
			}
		}
	}
	return indecies;
}

string DBGdetector::get_mem(HANDLE h){
	char szName[MAX_PATH] = {0};
	DWORD dwRet = 0, dwSize = _countof(szName);
	LPVOID address;

	string bytes = "";

	memset(szName, 0, sizeof(szName));    
    if ( (dwRet = GetProcessImageFileName(h, szName, _countof(szName))) <= 0 ){
        printf("fail to call GetProcessImageFileName()\n");
		return "";
	}
	else{
		string temp(szName), temp2 = "", filename = "";
		remove_if(temp.begin(), temp.end(), isspace);
		int j = temp.find_last_of('e'), i = temp.find_last_of('\\') + 1;
		for (i; i <= j; i++){
			temp2 += temp[i];
		}
		int x = temp2.find(".exe") + 4;
		for (int l = 0; l < x; l++){
			filename += temp2[l];
		}
		cout << "filename: " << filename << "/" << x << endl;

		HMODULE hMods[1024];
		DWORD cbNeeded;
		unsigned int k;


		if(EnumProcessModules(h, hMods, sizeof(hMods), &cbNeeded)) {
			for (k = 0; k < (cbNeeded/sizeof(HMODULE)); k++){
				char szModName[MAX_PATH];
				if (GetModuleFileNameEx(h,hMods[k], szModName, sizeof(szModName) / sizeof(TCHAR))){
					string modname = "", mod_temp(szModName);
					int j = mod_temp.find_last_of('e'), i = mod_temp.find_last_of('\\') + 1;
					for (i; i <= j; i++){
						modname += mod_temp[i];
					}
					if (modname == "Final.exe"){
						this_process = h;
					}
					if (modname == "devenv.exe"){
						vis_stu = h;
					}
					if (modname.compare(filename) == 0){
						MODULEINFO mi;
						if(!GetModuleInformation(h, hMods[k], &mi, sizeof(mi))){
							cout << "MI failed." << endl;
							return "";
						}
						else{
							cout << "MI found." << endl;
							address = mi.lpBaseOfDll;
						}
						uint8_t buff[2048*2];
						SIZE_T bytesRead;
						BOOL success = ReadProcessMemory(h, address, buff, 2048*2, &bytesRead);
						if (!success) cout << "Read Failed." << endl;
						bytes = bytes_to_hex(buff, bytesRead);
						//cout << bytes;
					}	
				}
			}
		}
		else{
			cout << "Enum failed." << endl;
			return "";
		}
	}
	cout << endl;
	return bytes;
}

bool DBGdetector::detect_api(HANDLE h){
	//uses CheckRemoteDebuggerPresent()

	BOOL bDebugged = FALSE;
	if (CheckRemoteDebuggerPresent(h , &bDebugged )){
		return true;
	}
	return false;
}

bool DBGdetector::detect_flags(string bytes){
	stringstream ss(bytes);
	string byte = "";

	for (int i = 0; i < 84; i++){
		byte = "";
		ss >> byte;
	}

	if(byte == "70")
		return true;
	return false;
}

bool DBGdetector::detect_exception(string bytes){
	if (bytes.find("CC") > 0)
		return true;
	return false;
}

void DBGdetector::kill_processes(vector< HANDLE > handles, vector<int> check){
	for (int i = 0; i < check.size(); i++){
		if (check[i] > 1)
			TerminateProcess(handles[i], 0);
	}
}

string DBGdetector::bytes_to_hex(uint8_t* buff, SIZE_T size){
	stringstream result;
	result << hex << uppercase << setfill('0');
	for (; size > 0; buff++, size--){
		result << setw(2) << (unsigned int) *buff;
		if (size > 1)
			result << " ";
	}
	return result.str();
}