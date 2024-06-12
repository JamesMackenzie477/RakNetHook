#include "Hooker.h"

// Creates a new hook object.
// pTarget - Address of function to hook.
// pHook - Address of function to direct calls to.
Hook::Hook(PVOID pTarget, PVOID pHook)
{
	// Sets the target function.
	this->pTarget = pTarget;
	// Adds the target function address to the shell code.
	*(PVOID*)&ShellCode[1] = pHook;
}

// Attaches the hook.
// Returns true if attachment succeeded.
BOOL Hook::Attach()
{
	// Checks if the hook is already attached to prevent errors.
	if (!Attached)
	{
		// Stores the original memory protection.
		DWORD OldProtect;
		// Changes the memory protection so we can write the function hook.
		if (VirtualProtect(pTarget, sizeof(ShellCode), PAGE_EXECUTE_READWRITE, &OldProtect))
		{
			// Saves the original bytes.
			memcpy(OriginalBytes, pTarget, sizeof(OriginalBytes));
			// Writes the redirect shell code.
			memcpy(pTarget, ShellCode, sizeof(ShellCode));
			// Restores the original protection.
			VirtualProtect(pTarget, sizeof(ShellCode), OldProtect, &OldProtect);
			// Hook is attached.
			Attached = TRUE;
			// Function succeeded.
			return TRUE;
		}
	}
	// Function failed.
	return FALSE;
}

// Detatches the hook.
// Returns true if detatchment succeeded.
BOOL Hook::Detatch()
{
	// Checks if the hook is attached to prevent errors.
	if (Attached)
	{
		// Stores the original memory protection.
		DWORD OldProtect;
		// Changes the memory protection so we can write the original bytes.
		if (VirtualProtect(pTarget, sizeof(OriginalBytes), PAGE_EXECUTE_READWRITE, &OldProtect))
		{
			// Writes the original bytes.
			memcpy(pTarget, OriginalBytes, sizeof(OriginalBytes));
			// Restores the original protection.
			VirtualProtect(pTarget, sizeof(OriginalBytes), OldProtect, &OldProtect);
			// Hook is detached.
			Attached = FALSE;
			// Function succeeded.
			return TRUE;
		}
	}
	// Function failed.
	return FALSE;
}