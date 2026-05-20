#pragma once
#include <Windows.h>
#include <cstddef>
#include <cstdint>

struct Player {

    std::byte pad_000[0x140];

    float Armor;             // 0x140
    float MaxArmor;          // 0x144
    std::byte pad_148[4];    
    float Health;            // 0x14C
    float Money;             // 0x150
    std::byte pad_154[12];  
    float Deaths;            // 0x160
    float Kills;             // 0x164
    float Scores;            // 0x168

    std::byte pad_16C[0x190 - 0x16C];


    float CameraFov;         // 0x190
    float SprintFovMult;     // 0x194
    std::byte pad_198[4];    // 0x198
    float WeaponCameraFOV;   // 0x19C
    std::byte pad_1A0[4];    // 0x1A0

    uint8_t IsImmune;        // 0x1A4 (Byte)

    std::byte pad_1A5[0x200 - 0x1A5];


    uintptr_t RecoilBar;     // 0x200 

    std::byte pad_208[0x310 - 0x208];


    uintptr_t PlayerMovement; // 0x310

 
    std::byte pad_318[0x338 - 0x318];

    uintptr_t CharacterController; // 0x338
    uintptr_t WeaponManager;       // 0x340 

    std::byte pad_350[0x428 - 0x350];

    uint8_t IsDead;          // 0x428 (Byte)

    std::byte pad_429[0x468 - 0x429];

    uint8_t IsShopOpen;      // 0x468 (Byte)
    uint8_t IsChatOpen;      // 0x469 (Byte)
    uint8_t IsPlanting;      // 0x46A (Byte)
    std::byte pad_46B[1];    
    uint8_t HasBomb;         // 0x46C (Byte)

    std::byte pad_46D[0x4C8 - 0x46D];

    float SprintMult;        // 0x4C8 
};