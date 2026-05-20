#pragma once
#include <cstdint>
#include "core/math/math.h"

typedef Vector3(__fastcall* fn_get_position)(void* __this, const void* method);
inline fn_get_position  oget_position = nullptr;

Vector3 __fastcall hget_position(void* __this, const void* method);

Vector3 GetPosition(void* __this);