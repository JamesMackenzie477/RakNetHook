#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include "RakNet.h"
#include "Hooker.h"
#include "Utils.h"
#include "Roblox.h"

// Defines various Roblox packet identifiers.
#define ID_ROBLOX_SCHEMA_VERSION (char)0x90
#define ID_ROBLOX_START_AUTH_THREAD (char)0x92
#define ID_ROBLOX_AUTH (char)0x8A
#define ID_ROBLOX_INITIAL_SPAWN_NAME (char)0x8F
#define ID_ROBLOX_UNKNOWN (char)0x83

// Allows for extraction of a packet identifier.
#define PACKET_IDENTIFIER(I) ((unsigned char)I[0])

using namespace std;

// Exposes the dump file.
extern ofstream DumpFile;

// Exposes the hook objects to other source files.
extern Hook* pStartupHook;
extern Hook* pConnectHook;
extern Hook* pSendHook;
extern Hook* pSendLoopbackHook;
extern Hook* pSendBufferedHook;
extern Hook* pSendBufferedListHook;
extern Hook* pReceiveHook;

extern Hook* pJoinServer;

// Exposes the hook functions to other source files.
namespace RakHook
{
	RakNet::StartupResult __fastcall Startup(RakNet::RakPeerInterface* instance, PVOID trash, unsigned int maxConnections, RakNet::SocketDescriptor *socketDescriptors, unsigned socketDescriptorCount, int threadPriority);
	RakNet::ConnectionAttemptResult __fastcall Connect(RakNet::RakPeerInterface* instance, PVOID trash, const char* host, unsigned short remotePort, const char *passwordData, int passwordDataLength, RakNet::PublicKey *publicKey, unsigned connectionSocketIndex, unsigned sendConnectionAttemptCount, unsigned timeBetweenSendConnectionAttemptsMS, RakNet::TimeMS timeoutTime);
	RakNet::uint32_t __fastcall Send(RakNet::RakPeerInterface* instance, PVOID trash, const char *data, const int length, RakNet::PacketPriority priority, RakNet::PacketReliability reliability, char orderingChannel, const RakNet::AddressOrGUID systemIdentifier, bool broadcast, RakNet::uint32_t forceReceiptNumber);
	void __fastcall SendLoopback(RakNet::RakPeerInterface* instance, PVOID trash, const char *data, const int length);
	void __fastcall SendBuffered(RakNet::RakPeerInterface* instance, PVOID trash, const char *data, RakNet::BitSize_t numberOfBitsToSend, RakNet::PacketPriority priority, RakNet::PacketReliability reliability, int a6, int a7, int a8, __int16 a9, int a10, char a11, int a12, int a13, int a14, int a15, int a16, int a17, int a18, bool broadcast, RakNet::RemoteSystemStruct::ConnectMode connectionMode, RakNet::uint32_t receipt, char a22);
	void __fastcall SendBufferedList(RakNet::RakPeerInterface* instance, PVOID trash, const char **data, const int *lengths, const int numParameters, RakNet::PacketPriority priority, RakNet::PacketReliability reliability, int a6, int a7, int a8, __int16 a9, int a10, char a11, int a12, int a13, int a14, int a15, int a16, int a17, int a18, bool broadcast, RakNet::RemoteSystemStruct::ConnectMode connectionMode, uint32_t receipt, char a22);
	RakNet::Packet* __fastcall Receive(RakNet::RakPeerInterface* instance, PVOID trash);

	int __fastcall JoinServer(RBX::PlayerConfigurer* PlayerConfigurer, void *trash, int a2, int *a3, std::string *pJSON, __int64 *a5);
}