#pragma once
#include <cstddef>
#include <cstdint>

typedef void(__fastcall* set_PrValue)(void* __this, float value, void* method);
inline set_PrValue oset_PrValue = nullptr;

void __fastcall hset_PrValue(void* __this, float value, void* method);

struct ProtectedFloat {
    std::byte data[16];

  
    void Set(float value) {
        if (oset_PrValue) {
            oset_PrValue(this, value, nullptr);
        }
    }
};