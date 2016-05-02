#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <vector>
#include <tchar.h>
#include <psapi.h>
#include <algorithm>
#include <string>
#include <cstdint>
#include <sstream>
#include <iomanip>

class DBGdetector{
	private: 
		std::vector<DWORD> processIDs;
		HANDLE this_process;
		HANDLE vis_stu;
	public:
		
		void detector(std::vector< HANDLE > handles);
		//void detector();
		//main hub for five detectors
		std::vector<int> detect_debugger(std::vector<HANDLE> handles);

		std::string get_mem(HANDLE h);

		//performs api based detection
		bool detect_api(HANDLE h);
		//perfroms detection using flags
		bool detect_flags(std::string bytes);
		//performs exception based detection
		bool detect_exception(std::string bytes);

		void kill_processes(std::vector< HANDLE > handles, std::vector<int> check);

		std::string bytes_to_hex(uint8_t* buff, SIZE_T size);
};