#include "RakNet.h"


// Defines various RakNet functions and definitions.
namespace RakNet
{
	void RakPeerInterface::SendBuffered(const char *data, BitSize_t numberOfBitsToSend, PacketPriority priority, PacketReliability reliability, int a6, int a7, int a8, __int16 a9, int a10, char a11, int a12, int a13, int a14, int a15, int a16, int a17, int a18, bool broadcast, RemoteSystemStruct::ConnectMode connectionMode, uint32_t receipt, char a22)
	{
		typedef void(__thiscall * _SendBuffered)(RakPeerInterface* instance, const char *data, BitSize_t numberOfBitsToSend, PacketPriority priority, PacketReliability reliability, int a6, int a7, int a8, __int16 a9, int a10, char a11, int a12, int a13, int a14, int a15, int a16, int a17, int a18, bool broadcast, RemoteSystemStruct::ConnectMode connectionMode, uint32_t receipt, char a22);
		_SendBuffered SendBuffered = (_SendBuffered)RakPeer::GetSendBuffered();
		return SendBuffered(this, data, numberOfBitsToSend, priority, reliability, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, broadcast, connectionMode, receipt, a22);
	}

	void RakPeerInterface::SendBufferedList(const char **data, const int *lengths, const int numParameters, PacketPriority priority, PacketReliability reliability, int a6, int a7, int a8, __int16 a9, int a10, char a11, int a12, int a13, int a14, int a15, int a16, int a17, int a18, bool broadcast, RemoteSystemStruct::ConnectMode connectionMode, uint32_t receipt, char a22)
	{
		typedef void(__thiscall * _SendBufferedList)(RakPeerInterface* instance, const char **data, const int *lengths, const int numParameters, PacketPriority priority, PacketReliability reliability, int a6, int a7, int a8, __int16 a9, int a10, char a11, int a12, int a13, int a14, int a15, int a16, int a17, int a18, bool broadcast, RemoteSystemStruct::ConnectMode connectionMode, uint32_t receipt, char a22);
		_SendBufferedList SendBufferedList = (_SendBufferedList)RakPeer::GetSendBufferedList();
		return SendBufferedList(this, data, lengths, numParameters, priority, reliability, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, broadcast, connectionMode, receipt, a22);
	}

	// Gets the RakNet peer class virtual functions.
	RakPeer* RakPeer::Get()
	{
		// Constructs and returns the address of the rak peer vftable.
		return (RakPeer*)((LPBYTE)GetModuleHandleW(L"RobloxPlayerBeta.exe") + 0x150E730);
	}

	// Gets the RakPeer send buffered method.
	PVOID RakPeer::GetSendBuffered()
	{
		// Constructs and returns the address of the RakPeer send buffered method.
		return (PVOID)((LPBYTE)GetModuleHandleW(L"RobloxPlayerBeta.exe") + 0x951060);
	}

	// Gets the RakPeer send buffered list method.
	PVOID RakPeer::GetSendBufferedList()
	{
		// Constructs and returns the address of the RakPeer send buffered method.
		return (PVOID)((LPBYTE)GetModuleHandleW(L"RobloxPlayerBeta.exe") + 0x951200);
	}
}