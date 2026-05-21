#pragma once

#define PRESENT_PATTERN "48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 54 41 56 41 57 48 83 EC ? 41 8B E8"

namespace Hooks
{

	bool Init();

	bool SetupPresentHook();
	bool SetupPlayerUpdateHook();
	bool SetupGetPositionHook();
	bool SetupGetTransformHook();
	bool SetupGetPrValueHook();
	bool SetupSetPrValueHook();
	bool SetupGunUpdateHook();
	bool SetupMovementUpdateHook();
	bool SetupW2screenHook();
	bool SetupBoneTransformHook();
	void Shutdown();
}