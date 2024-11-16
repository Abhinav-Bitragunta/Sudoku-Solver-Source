#pragma once

#include <cmath>

#include <cstddef>

#include <format>
#include <iostream>

#include <array>
#include <vector>
#include <string>

//Timing
#include <chrono>


//DO NOT uncomment this unless you specifically want to enter debug mode.
// #define DEBUG

#ifdef DEBUG
#define LOG(x) std::cout << x << '\n'
#else
#define LOG(X) 
#endif