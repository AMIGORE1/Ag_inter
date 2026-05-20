#pragma once
#include <cstdint>
#include <Windows.h>
#include <string>
#include <Psapi.h>
#include <vector>

inline uintptr_t moduleBase = 0;

namespace Mem
{
    uintptr_t PatternScan(const std::string& pattern, const std::string& module);
    bool Init_module();

    template<typename t>
    inline bool write(uintptr_t addr, t buffer) {
        reinterpret_cast<t>(addr) = buffer;
        return true;
    }

    template<typename t>
    inline t read(uintptr_t addr) {
        if (addr == 0) return t{};
        return reinterpret_cast<t>(addr);
    }
}