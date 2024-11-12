#pragma once

#include <iostream>
#include <format>
#include <cstddef>
#include <cmath>
#include <array>
#include <vector>
#include <string>

//Timing
#include <chrono>
//To check memory usage
#include <windows.h>
#include <psapi.h>

//DO NOT uncomment this unless you specifically want to enter debug mode.
// #define DEBUG

#ifdef DEBUG
#define LOG(x) std::cout << x << '\n'
#else
#define LOG(X) 
#endif