#pragma once
#include <Windows.h>
#include "havoc/classes/player_movement.h"
#include "core/global/config.h"

extern PlayerMovementData* cachedMovementData;

typedef void(__fastcall* fnMovementUpdate)(void* __this, const void* method);
inline fnMovementUpdate oMovementUpdate = nullptr;

void hMovementUpdate(void* __this, const void* method);

void ApplyMovementHacks();

