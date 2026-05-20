#pragma once
#include <cstdio>
#include "havoc/classes/wpn_stats.h"
#include "core/global/config.h"

extern CachedWeaponStats* cachedWeaponStats;

typedef void(__fastcall* GunUpdate)(void* __this, const void* method);
inline GunUpdate oGunUpdate = nullptr;

void __fastcall hGunUpdate(void* __this, const void* method);

void ApplyWeaponHacks();