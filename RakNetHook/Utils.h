#pragma once
#include <sstream>
#include <iomanip>

namespace std
{
	// Converts a byte array to a std::string.
	std::string to_string(const char * bytes, int length);
}