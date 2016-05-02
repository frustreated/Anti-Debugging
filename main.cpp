#include "dbgdetector.h"

using namespace std;

vector<DWORD> processIDs;


BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam){
	DWORD processID;
	GetWindowThreadProcessId(hwnd, &processID);
	processIDs.push_back(processID);
	return TRUE;
}

int main(){
	while(true){
		EnumWindows(EnumWindowsProc, NULL);
		sort(processIDs.begin(), processIDs.end());
		processIDs.erase(unique(processIDs.begin(),processIDs.end() ),processIDs.end() );
		vector<HANDLE> handles;
		for (int i = 0; i < processIDs.size(); i++){
			HANDLE h = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processIDs[i]);
			handles.push_back(h);
		}

		DBGdetector dbg;
		dbg.detector(handles);

		for (int i = 0; i < processIDs.size(); i++){
			CloseHandle(handles[i]);
		}
	}

	int b;
	cin >> b;
    return 0;
}


