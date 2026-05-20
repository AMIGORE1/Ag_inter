#pragma once
#include <cstdio>
#include "havoc/classes/player.h"
#include "havoc/hooks/get-set/get_pos/get_pos.h"
#include "core/math/math.h"
#include "havoc/hooks/w2screen/w2screen.h"

extern Player* localPlayer;

typedef void(__fastcall* fnFpsPlayerUpdate)(void* __this, const void* method);
inline fnFpsPlayerUpdate oFpsPlayerUpdate = nullptr;

void __fastcall hFpsPlayerUpdate(void* __this, const void* method);
