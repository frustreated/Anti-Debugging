#include "dbgdetector.h"
using namespace std;

DBGdetector::DBGdetector(){
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
	if (detect_api()){
		return 1;
	}
	if (detect_flags()){
		return 2;
	}
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
	return true;
}

bool DBGdetector::detect_hardware(){
	return true;
}

bool DBGdetector::detect_exception(){
	return true;
}

bool DBGdetector::detect_timing(){
	return true;
}
