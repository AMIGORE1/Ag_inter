#pragma once
#include <cstdint>

typedef uintptr_t(__fastcall* fn_get_transform)(void* __this, const void* method);
inline fn_get_transform oget_transform = nullptr;

uintptr_t __fastcall hget_transform(void* __this, const void* method);