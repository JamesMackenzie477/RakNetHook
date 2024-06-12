#pragma once
#include <Windows.h>
#include <string>

namespace RBX
{
	class PlayerConfigurer
	{
	public:
		int JoinServer(int a2, int * a3, std::string * pJSON, __int64 * a5);
		static void* GetJoinServer();
	};
}