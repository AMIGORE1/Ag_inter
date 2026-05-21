#pragma once
#include <cstdint>

namespace offsets
{
	namespace fn
	{
		constexpr uintptr_t FPSplrUpdate = 0x522080;
		constexpr uintptr_t GunLateUpdate = 0x54F4B0;
		constexpr uintptr_t WeaponManagerUpdate = 0x5CD540;
		constexpr uintptr_t PlayerMovementUpdate = 0x578640;
		constexpr uintptr_t GetBone = 0x211D570;
		constexpr uintptr_t WorldToScreenPoint = 0x212BD60;

		constexpr uintptr_t get_Transform = 0x215E5C0;
		constexpr uintptr_t get_Position = 0x21751B0;
		constexpr uintptr_t set_Position = 0x21759C0;
	

		constexpr uintptr_t get_ProtectedValue = 0x165CB00;
		constexpr uintptr_t set_ProtectedValue = 0x165D070;
	}
}