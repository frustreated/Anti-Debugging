#include "dbgdetector.h"
using namespace std;
BOOL WINAPI IsDebuggerPresent(void);
void DBGdetector::detector(){
	int check = detect_debugger();
	string message = "Debugger detected! \n";
	switch (check){
		case 1:
			message += "Detection: API.";
			MessageBox(0, message.c_str(), "Warning", MB_OK);
			break;
		case 2:
			message += "Detection: FLAGS.";
			MessageBox(0, message.c_str(), "Warning", MB_OK);
			break;
		case 3:
			message += "Detection: HARDWARE.";
			MessageBox(0, message.c_str(), "Warning", MB_OK);
			break;
		case 4:
			message += "Detection: EXCEPTION.";
			MessageBox(0, message.c_str(), "Warning", MB_OK);
			break;
		case 5:
			message += "Detection: TIMING.";
			MessageBox(0, message.c_str(), "Warning", MB_OK);
			break;
		default:
			cout << "Normal Execution." << endl;
			break;
	}
}
int DBGdetector::detect_debugger(){
	/*if (detect_api()){
		return 1;
	}
	if (detect_flags()){
		return 2;
	}*/
	if (detect_hardware()){
		return 3;
	}
	if (detect_exception()){
		return 4;
	}
	if (detect_timing()){
		return 5;
	}
	
	return -1;

}
bool DBGdetector::detect_api(){
	//uses two methods: IsDebuggerPresent() and FindWindow()
	
	if(IsDebuggerPresent()){
		return true;
	}

	if(FindWindow("tidawindow", 0)){
		return true;
	}

	return false;
}

bool DBGdetector::detect_flags(){
	/*__asm{ 
		mov eax, fs:[0x18]
		mov eax, [eax+0x30]
		mov eax, [eax+0x68]
		test eax, 0x70
		jz  nodebugger
	}*/
	unsigned long NTGlobalFlags = 0;

	__asm{
		mov eax, fs:[30h]
		mov eax, [eax + 68h]
		mov NTGlobalFlags, eax
	}

	if (NTGlobalFlags & 0x70){
		return true;
	}
	return false;
}

bool DBGdetector::detect_hardware(){
	unsigned int NumBps = 0;

	CONTEXT context;
	ZeroMemory(&context, sizeof(CONTEXT));

	context.ContextFlags = CONTEXT_DEBUG_REGISTERS;
	HANDLE hThread = GetCurrentThread();

	if (GetThreadContext(hThread, &context) == 0)
		NumBps = -1;

	if (context.Dr0 != 0)
		NumBps++;
	if (context.Dr1 != 0)
		NumBps++;
	if (context.Dr2 != 0)
		NumBps++;
	if (context.Dr3 != 0)
		NumBps++;

	if (NumBps > 0)
		return true;
	return false;
}

bool DBGdetector::detect_exception(){
	return false;
}

bool DBGdetector::detect_timing(){
	long timing = -100; // reasonalbe amount of buffer time
	DWORD start = GetTickCount();
	int j = 0;
	__asm{
		xor ebx, ebx
	}
	for (int i = 0; i < 5000; i++){
		for (int k = 0; k < 5000; k++){
			j++;
		}
	}
	DWORD end = GetTickCount();
	long diff = start-end;
	if (diff < timing){
		return true;
	}
	return false;
}
