#pragma once
#include "core/math/math.h"
#include <vector>
#include <mutex>
#include <algorithm>
#include "../ext/imgui/imgui.h"
#include "core/global/config.h"

struct PlayerInfo
{
    Vector3 worldPos;
    float health;
    float armor;
    bool isDead;
};

typedef Vector3(__fastcall* fn_WorldToScreenPoint)(void* camera, Vector3 position, const void* method);
inline fn_WorldToScreenPoint oWorldToScreenPoint = nullptr;

Vector3 __fastcall hWorldToScreenPoint(void* camera, Vector3 position, const void* method);

namespace Esp
{
    inline ImVec4 boxColor = { 1.f, 0.f, 0.f, 1.f };
    inline ImVec4 lineColor = { 0.f, 1.f, 0.f, 0.5f };
    inline ImVec4 textColor = { 1.f, 1.f, 1.f, 1.f };
    inline ImVec4 deadColor = { 0.5f, 0.5f, 0.5f, 1.f };

    inline ImU32 ToU32(ImVec4 c);

    inline std::mutex playersMutex;          
    inline std::vector<PlayerInfo> players;
    extern void* currentCamera;
    inline bool showDeadPlayers = false;
    inline float boxThickness = 1.5f;
    void Draw();
}