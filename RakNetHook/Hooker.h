#pragma once
#include <Windows.h>

// Consider using a hooking library since this one may not work with multi-threaded programs.

// Stores a hook object.
// Allows for manipulation of a hook.
class Hook
{
private:
	// Stores the hook shell code.
	BYTE ShellCode[6] = { 0x68, 0x00, 0x00, 0x00, 0x00, 0xC3 };
	// Is the hook attached.
	BOOL Attached = FALSE;
	// Stores the original function bytes.
	BYTE OriginalBytes[6];
public:
	// Stores the target function.
	PVOID pTarget;
	// Creates a new hook object.
	// pTarget - Address of function to hook.
	// pHook - Address of function to direct calls to.
	Hook(PVOID pTarget, PVOID pHook);
	// Attaches the hook.
	// Returns true if attachment succeeded.
	BOOL Attach();
	// Detatches the hook.
	// Returns true if detatchment succeeded.
	BOOL Detatch();
};