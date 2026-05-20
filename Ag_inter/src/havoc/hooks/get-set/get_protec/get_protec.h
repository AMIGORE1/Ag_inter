#pragma once


typedef float(__fastcall* get_PrValue)(void* __this, void* method);
inline get_PrValue oget_PrValue = nullptr;

float __fastcall hget_PrValue(void* __this, void* method);