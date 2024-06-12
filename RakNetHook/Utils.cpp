#include "Utils.h"

// Converts a byte array to a std::string.
std::string std::to_string(const char * bytes, int length)
{
	std::stringstream ss;
	ss << std::hex << std::setfill('0');
	for (int i = 0; i < length; i++) ss << std::setw(2) << static_cast<int>(bytes[i]);
	return ss.str();
}
