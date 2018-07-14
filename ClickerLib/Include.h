#pragma once

#include <thread>
#include <atomic>
#include <vector>
#include <mutex>

#ifdef _LIBRARY
	#include "Vector2.h"
#else
	#include "Communication.h"
	#include "Settings.h"
	#include "Clicker.h"
#endif
