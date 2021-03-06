#pragma once

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// Custom auto clicking library
#include "../ClickerLib/include.h"

#ifdef _DEBUG
	#ifndef _WIN64
		#pragma comment(lib, "../Debug/ClickerLib.lib")
	#else
		#pragma comment(lib, "../x64/Debug/ClickerLib.lib")
	#endif
#else
	#ifndef _WIN64
		#pragma comment(lib, "../Release/ClickerLib.lib")
	#else
		#pragma comment(lib, "../x64/Release/ClickerLib.lib")
	#endif
#endif

// Common controls
#include <CommCtrl.h>
#pragma comment(lib, "Comctl32.lib")
#pragma comment(linker,"\"/manifestdependency:type                  = 'win32' \
                                              name                  = 'Microsoft.Windows.Common-Controls' \
                                              version               = '6.0.0.0' \
                                              processorArchitecture = '*' \
                                              publicKeyToken        = '6595b64144ccf1df' \
                                              language              = '*'\"")