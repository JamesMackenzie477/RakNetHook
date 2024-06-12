#include "Roblox.h"

int RBX::PlayerConfigurer::JoinServer(int a2, int * a3, std::string * pJSON, __int64 * a5)
{
	typedef int(__thiscall * _JoinServer)(PlayerConfigurer* instance, int a2, int * a3, std::string * pJSON, __int64 * a5);
	_JoinServer JoinServer = (_JoinServer)PlayerConfigurer::GetJoinServer();
	return JoinServer(this, a2, a3, pJSON, a5);
}

void * RBX::PlayerConfigurer::GetJoinServer()
{
	return (void *)((LPBYTE)GetModuleHandleW(L"RobloxPlayerBeta.exe") + 0x8DF840);
}
