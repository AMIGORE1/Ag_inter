#include "bone_esp.h"

// -------------------------------------------------------
//  Hook: просто форвардимо оригінал (можна розширити)
// -------------------------------------------------------
uintptr_t __fastcall hGetBoneTransformInternal(void* animator, int boneId, const void* method)
{
    return oGetBoneTransformInternal(animator, boneId, method);
}

// -------------------------------------------------------
//  Отримати world-position кістки
// -------------------------------------------------------
Vector3 BoneEsp::GetBoneWorldPos(void* animator, HumanBodyBones bone)
{
    if (!animator || !oGetBoneTransformInternal || !oget_position)
        return { 0.f, 0.f, 0.f };

    uintptr_t boneTransform = oGetBoneTransformInternal(animator, static_cast<int>(bone), nullptr);
    if (!boneTransform)
        return { 0.f, 0.f, 0.f };

    return oget_position(reinterpret_cast<void*>(boneTransform), nullptr);
}

// -------------------------------------------------------
//  Малюємо bone ESP
// -------------------------------------------------------
void BoneEsp::Draw()
{
    if (!showBoneEsp) return;
    if (!oWorldToScreenPoint || !Esp::currentCamera) return;

    ImDrawList* dl = ImGui::GetBackgroundDrawList();
    if (!dl) return;

    ImGuiIO& io = ImGui::GetIO();
    float screenW = io.DisplaySize.x;
    float screenH = io.DisplaySize.y;

    // Повний список ребер скелету (16 + 3 права нога)
    static const std::vector<BoneConnection> BONES = {
        // хребет
        { HumanBodyBones::Hips,          HumanBodyBones::Spine        },
        { HumanBodyBones::Spine,         HumanBodyBones::Chest        },
        { HumanBodyBones::Chest,         HumanBodyBones::UpperChest   },
        { HumanBodyBones::UpperChest,    HumanBodyBones::Neck         },
        { HumanBodyBones::Neck,          HumanBodyBones::Head         },
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
        { HumanBodyBones::Hips,          HumanBodyBones::RightUpperLeg  },
        { HumanBodyBones::RightUpperLeg, HumanBodyBones::RightLowerLeg  },
        { HumanBodyBones::RightLowerLeg, HumanBodyBones::RightFoot      },
    };

    std::lock_guard<std::mutex> lock(bonePlayersMutex);

    for (auto& player : bonePlayers)
    {
        if (player.isDead) continue;
        if (!player.animatorPtr) continue;

        ImU32 col = player.isDead
            ? IM_COL32(100, 100, 100, 255)
            : IM_COL32(
                (int)(boneColor.x * 255),
                (int)(boneColor.y * 255),
                (int)(boneColor.z * 255),
                (int)(boneColor.w * 255));

        for (auto& conn : BONES)
        {
            Vector3 worldA = GetBoneWorldPos(player.animatorPtr, conn.from);
            Vector3 worldB = GetBoneWorldPos(player.animatorPtr, conn.to);

            // Якщо кістка не знайдена — пропускаємо
            if (worldA.x == 0.f && worldA.y == 0.f && worldA.z == 0.f) continue;
            if (worldB.x == 0.f && worldB.y == 0.f && worldB.z == 0.f) continue;

            Vector3 screenA = oWorldToScreenPoint(Esp::currentCamera, worldA, nullptr);
            Vector3 screenB = oWorldToScreenPoint(Esp::currentCamera, worldB, nullptr);

            // z < 0 → за камерою
            if (screenA.z < 0.01f || screenB.z < 0.01f) continue;

            // Відсікаємо якщо обидві точки повністю за межами екрану
            if (screenA.x < 0 && screenB.x < 0) continue;
            if (screenA.x > screenW && screenB.x > screenW) continue;
            if (screenA.y < 0 && screenB.y < 0) continue;
            if (screenA.y > screenH && screenB.y > screenH) continue;

            dl->AddLine(
                ImVec2(screenA.x, screenA.y),
                ImVec2(screenB.x, screenB.y),
                col,
                boneThickness
            );
        }
    }
}