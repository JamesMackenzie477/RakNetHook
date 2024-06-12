#include "RakNetHook.h"

// Stores the dump file.
ofstream DumpFile;

// Stores the hook objects.
Hook* pStartupHook;
Hook* pConnectHook;
Hook* pSendHook;
Hook* pSendLoopbackHook;
Hook* pSendBufferedHook;
Hook* pSendBufferedListHook;
Hook* pReceiveHook;

Hook* pJoinServer;

// Adds the RakNet hooks.
DWORD WINAPI AddRakNetHooks(_In_ LPVOID lpParameter)
{
	// Opens the dump file.
	DumpFile.open("Dump.txt");
	// Gets the RakNet peer vftable.
	// RakNet::RakPeer* pRakPeer = RakNet::RakPeer::Get();
	// Creates the function hook objects.
	// pStartupHook = new Hook(pRakPeer->Startup, RakHook::Startup);
	// pConnectHook = new Hook(pRakPeer->Connect, RakHook::Connect);
	// pSendHook = new Hook(pRakPeer->Send, RakHook::Send);
	// pSendLoopbackHook = new Hook(pRakPeer->SendLoopback, SendLoopbackHook);
	pSendBufferedHook = new Hook(RakNet::RakPeer::GetSendBuffered(), RakHook::SendBuffered);
	// pSendBufferedListHook = new Hook(RakNet::RakPeer::GetSendBufferedList(), RakHook::SendBufferedList);
	// pReceiveHook = new Hook(pRakPeer->Receive, RakHook::Receive);
	// pJoinServer = new Hook(RBX::PlayerConfigurer::GetJoinServer(), RakHook::JoinServer);
	// Attaches the hooks.
	// if (!pStartupHook->Attach()) return FALSE;
	// if (!pConnectHook->Attach()) return FALSE;
	// if (!pSendHook->Attach()) return FALSE;
	// if (!pSendLoopbackHook->Attach()) return FALSE;
	if (!pSendBufferedHook->Attach()) return FALSE;
	// if (!pSendBufferedListHook->Attach()) return FALSE;
	// if (!pReceiveHook->Attach()) return FALSE;
	// if (!pJoinServer->Attach()) return FALSE;
	return TRUE;
}

// Removes the RakNet hooks.
DWORD WINAPI RemoveRakNetHooks(_In_ LPVOID lpParameter)
{
	// Removes all of the hooks.
	// if (!pStartupHook->Detatch()) return FALSE;
	// if (!pConnectHook->Detatch()) return FALSE;
	// if (!pSendHook->Detatch()) return FALSE;
	// if (!pSendLoopbackHook->Detatch()) return FALSE;
	if (!pSendBufferedHook->Detatch()) return FALSE;
	// if (!pSendBufferedListHook->Detatch()) return FALSE;
	// if (!pReceiveHook->Detatch()) return FALSE;
	// if (!pJoinServer->Detatch()) return FALSE;
	// Deletes the hook objects.
	// delete pStartupHook;
	// delete pConnectHook;
	// delete pSendHook;
	// delete pSendLoopbackHook;
	delete pSendBufferedHook;
	// delete pSendBufferedListHook;
	// delete pReceiveHook;
	// delete pJoinServer;
	// Closes the dump file.
	DumpFile.close();
	// Function succeeded.
	return TRUE;
}

// Defines the main entry point of the library.
BOOL WINAPI DllMain(_In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason, _In_ LPVOID lpvReserved)
{
	// Checks the reason for the callback.
	// This is so the library can determine if RakNet should be hooked.
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		// If the library is being attached to a process.
		// Creates a thread to add the RakNet hooks.
		CreateThread(NULL, NULL, AddRakNetHooks, NULL, NULL, NULL);
		// Returns true.
		break;
	case DLL_PROCESS_DETACH:
		// If the library is being removed from a process.
		// Creates a thread to remove the RakNet hooks.
		CreateThread(NULL, NULL, RemoveRakNetHooks, NULL, NULL, NULL);
		// Returns true.
		break;
	}
	// Function succeeded.
	return TRUE;
}