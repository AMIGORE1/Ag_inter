#include "hooks.h"
#include <cstdio>
#include <thread>
#include "minhook/include/MinHook.h"
#include "core/mem/mem.h"
#include "havoc/offsets/offsets.h"

#include "present/present.h"
#include "plr_update/plr_update.h"
#include "get-set/get_trans/get_trans.h"
#include "get-set/get_pos/get_pos.h"
#include "get-set/get_protec/get_protec.h"
#include "get-set/set_protec/set_protec.h"
#include "gun_update/gun_update.h"
#include "move_update/move_update.h"
#include "w2screen/w2screen.h"
#include "bone_esp/bone_esp.h"

bool Hooks::Init()
{
    if (MH_Initialize() != MH_OK)
        return false;
    if (!SetupPresentHook())
        return false;
	if (!SetupPlayerUpdateHook())
        return false;
	if (!SetupGetTransformHook())
        return false;
	if (!SetupGetPositionHook())
        return false;
	if (!SetupGetPrValueHook())
        return false;
	if (!SetupSetPrValueHook())
        return false;
	if (!SetupGunUpdateHook())
        return false;
	if (!SetupMovementUpdateHook())
        return false;
    if (!SetupW2screenHook())
        return false;
    MH_EnableHook(MH_ALL_HOOKS);
    return true;
}

bool Hooks::SetupPresentHook()
{
    uintptr_t presentAddr = Mem::PatternScan(PRESENT_PATTERN, "GameOverlayRenderer64.dll");
    printf("[+] Pattern scan Present: 0x%llX\n", presentAddr);

    if (!presentAddr)
        return false;

    if (MH_CreateHook(reinterpret_cast<LPVOID>(presentAddr), &hkPresent, reinterpret_cast<LPVOID*>(&oPresent)) != MH_OK)
    {
        printf("[-] MH_CreateHook PRESENT FAILED\n");
        return false;
    }

    printf("[+] PRESENT Hook ENABLED successfully!\n");
    return true;
}

bool Hooks::SetupPlayerUpdateHook()
{
    if (MH_CreateHook(reinterpret_cast<LPVOID>(moduleBase + offsets::fn::FPSplrUpdate), &hFpsPlayerUpdate, reinterpret_cast<LPVOID*>(&oFpsPlayerUpdate)) != MH_OK)
    {
        printf("[-] MH_CreateHook PLAYER UPDATE FAILED\n");
        return false;
    }

    printf("[+] PLAYER UPDATE Hook ENABLED successfully!\n");
    return true;
}

bool Hooks::SetupGetPositionHook()
{
    if (MH_CreateHook(reinterpret_cast<LPVOID>(moduleBase + offsets::fn::get_Position), &hget_position, reinterpret_cast<LPVOID*>(&oget_position)) != MH_OK)
    {
        printf("[-] MH_CreateHook GET_POSITION  FAILED\n");
        return false;
    }

    printf("[+] GET_POSITION Hook ENABLED successfully!\n");
    return true;
}

bool Hooks::SetupGetTransformHook()
{
    if (MH_CreateHook(reinterpret_cast<LPVOID>(moduleBase + offsets::fn::get_Transform), &hget_transform, reinterpret_cast<LPVOID*>(&oget_transform)) != MH_OK)
    {
        printf("[-] MH_CreateHook GET_TRANSFORM  FAILED\n");
        return false;
    }

    printf("[+] GET_TRANSFORM  Hook ENABLED successfully!\n");
    return true;
}

bool Hooks::SetupGetPrValueHook()
{
    if (MH_CreateHook(reinterpret_cast<LPVOID>(moduleBase + offsets::fn::get_ProtectedValue), &hget_PrValue, reinterpret_cast<LPVOID*>(&oget_PrValue)) != MH_OK)
    {
        printf("[-] MH_CreateHook GET_PROTECTED FAILED\n");
        return false;
    }

    printf("[+] GET_PROTECTED Hook ENABLED successfully!\n");
    return true;
}

bool Hooks::SetupSetPrValueHook()
{
    if (MH_CreateHook(reinterpret_cast<LPVOID>(moduleBase + offsets::fn::set_ProtectedValue), &hset_PrValue, reinterpret_cast<LPVOID*>(&oset_PrValue)) != MH_OK)
    {
        printf("[-] MH_CreateHook SET_PROTECTED FAILED\n");
        return false;
    }

    printf("[+] SET_PROTECTED Hook ENABLED successfully!\n");
    return true;
}

bool Hooks::SetupGunUpdateHook()
{
    if (MH_CreateHook(reinterpret_cast<LPVOID>(moduleBase + offsets::fn::GunLateUpdate), &hGunUpdate, reinterpret_cast<LPVOID*>(&oGunUpdate)) != MH_OK)
    {
        printf("[-] MH_CreateHook GUN_UPDATE FAILED\n");
        return false;
    }

    printf("[+] GUN_UPDATE Hook ENABLED successfully!\n");
    return true;
}

bool Hooks::SetupMovementUpdateHook()
{
    if (MH_CreateHook(reinterpret_cast<LPVOID>(moduleBase + offsets::fn::PlayerMovementUpdate), &hMovementUpdate, reinterpret_cast<LPVOID*>(&oMovementUpdate)) != MH_OK)
    {
        printf("[-] MH_CreateHook MOVEMENT FAILED\n");
        return false;
    }

    printf("[+] MOVEMENT Hook ENABLED successfully!\n");
    return true;
}

bool Hooks::SetupW2screenHook()
{
    if (MH_CreateHook(reinterpret_cast<LPVOID>(moduleBase + offsets::fn::WorldToScreenPoint), &hWorldToScreenPoint, reinterpret_cast<LPVOID*>(&oWorldToScreenPoint)) != MH_OK)
    {
        printf("[-] MH_CreateHook W2screen FAILED\n");
        return false;
    }

    printf("[+] W2screen Hook ENABLED successfully!\n");
    return true;
}

bool Hooks::SetupBoneTransformHook()
{
    if (MH_CreateHook(
        reinterpret_cast<LPVOID>(moduleBase + 0x212BD60),
        &hGetBoneTransformInternal,
        reinterpret_cast<LPVOID*>(&oGetBoneTransformInternal)) != MH_OK)
    {
        printf("[-] MH_CreateHook BONE_TRANSFORM FAILED\n");
        return false;
    }
    printf("[+] BONE_TRANSFORM Hook ENABLED successfully!\n");
    return true;
}

void Hooks::Shutdown()
{
    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);
    MH_Uninitialize();
}
