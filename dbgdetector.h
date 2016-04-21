#include <iostream>
#include <Windows.h>
#include <stdio.h>


class DBGdetector{
	private:
		BOOL WINAPI IsDebuggerPresent(void);
	public:
		DBGdetector();

		//main hub for five detectors
		int detect_debugger();

		//performs api based detection
		bool detect_api();
		//perfroms detection using flags
		bool detect_flags();
		//performs hardware assisted detection
		bool detect_hardware();
		//performs exception based detection
		bool detect_exception();
		//performs timing based detection
		bool detect_timing();
};