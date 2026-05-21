#pragma once
#include "core/math/math.h"
#include "havoc/hooks/w2screen/w2screen.h"
#include "havoc/hooks/get-set/get_pos/get_pos.h"
#include <vector>
#include <array>

// -------------------------------------------------------
//  GetBoneTransformInternal hook
//  RVA: 0x211D570  (з base.txt Animator.GetBoneTransformInternal)
// -------------------------------------------------------
typedef uintptr_t(__fastcall* fn_GetBoneTransformInternal)(void* animator, int boneId, const void* method);
inline fn_GetBoneTransformInternal oGetBoneTransformInternal = nullptr;

uintptr_t __fastcall hGetBoneTransformInternal(void* animator, int boneId, const void* method);

// -------------------------------------------------------
//  HumanBodyBones  (з bone.txt)
// -------------------------------------------------------
enum class HumanBodyBones : int
{
    Hips = 0,
    LeftUpperLeg = 1,
    RightUpperLeg = 2,
    LeftLowerLeg = 3,
    RightLowerLeg = 4,
    LeftFoot = 5,
    RightFoot = 6,
    Spine = 7,
    Chest = 8,
    Neck = 9,
    Head = 10,
    LeftShoulder = 11,
    RightShoulder = 12,
    LeftUpperArm = 13,
    RightUpperArm = 14,
    LeftLowerArm = 15,
    RightLowerArm = 16,
    LeftHand = 17,
    RightHand = 18,
    LeftToes = 19,
    RightToes = 20,
    LeftEye = 21,
    RightEye = 22,
    Jaw = 23,
    UpperChest = 54,
    LastBone = 55,
};

// -------------------------------------------------------
//  Пара кісток → один відрізок скелету
// -------------------------------------------------------
struct BoneConnection
{
    HumanBodyBones from;
    HumanBodyBones to;
};

// Скелет: список ребер
static const std::array<BoneConnection, 16> SKELETON_CONNECTIONS = { {
        // хребет
        { HumanBodyBones::Hips,          HumanBodyBones::Spine      },
        { HumanBodyBones::Spine,         HumanBodyBones::Chest      },
        { HumanBodyBones::Chest,         HumanBodyBones::UpperChest },
        { HumanBodyBones::UpperChest,    HumanBodyBones::Neck       },
        { HumanBodyBones::Neck,          HumanBodyBones::Head       },
        // ліва рука
        { HumanBodyBones::UpperChest,    HumanBodyBones::LeftShoulder  },
        { HumanBodyBones::LeftShoulder,  HumanBodyBones::LeftUpperArm  },
        { HumanBodyBones::LeftUpperArm,  HumanBodyBones::LeftLowerArm  },
        { HumanBodyBones::LeftLowerArm,  HumanBodyBones::LeftHand      },
        // права рука
        { HumanBodyBones::UpperChest,    HumanBodyBones::RightShoulder  },
        { HumanBodyBones::RightShoulder, HumanBodyBones::RightUpperArm  },
        { HumanBodyBones::RightUpperArm, HumanBodyBones::RightLowerArm  },
        { HumanBodyBones::RightLowerArm, HumanBodyBones::RightHand      },
        // ліва нога
        { HumanBodyBones::Hips,          HumanBodyBones::LeftUpperLeg  },
        { HumanBodyBones::LeftUpperLeg,  HumanBodyBones::LeftLowerLeg  },
        { HumanBodyBones::LeftLowerLeg,  HumanBodyBones::LeftFoot      },
        // права нога
    } };

// Окремо — щоб не ламати constexpr розмір масиву
// Додаємо праву ногу динамічно у Draw (або збільшуємо масив нижче)

// -------------------------------------------------------
//  Дані одного гравця для bone ESP
// -------------------------------------------------------
struct BonePlayerInfo
{
    void* animatorPtr;  // вказівник на Animator компонент гравця
    bool  isDead;
};

namespace BoneEsp
{
    inline std::mutex               bonePlayersMutex;
    inline std::vector<BonePlayerInfo> bonePlayers;

    inline ImVec4  boneColor = { 0.0f, 1.0f, 0.5f, 1.0f };
    inline ImVec4  boneColorDead = { 0.4f, 0.4f, 0.4f, 1.0f };
    inline float   boneThickness = 1.2f;
    inline bool    showBoneEsp = false;

    // Отримати world-position кістки через оригінальний GetBoneTransformInternal + oget_position
    Vector3 GetBoneWorldPos(void* animator, HumanBodyBones bone);

    // Намалювати скелет усіх гравців
    void Draw();
}