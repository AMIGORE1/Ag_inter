#include "plr_update.h"


Player* localPlayer = nullptr;

void __fastcall hFpsPlayerUpdate(void* __this, const void* method)
{
    localPlayer = reinterpret_cast<Player*>(__this);

    uintptr_t listPtr = *(uintptr_t*)((uintptr_t)__this + 0x598);
    if (!listPtr) return oFpsPlayerUpdate(__this, method);

    int count = *(int*)(listPtr + 0x18);
    if (count <= 0 || count > 64) return oFpsPlayerUpdate(__this, method);

    uintptr_t itemsArray = *(uintptr_t*)(listPtr + 0x10);
    if (!itemsArray) return oFpsPlayerUpdate(__this, method);

    std::vector<PlayerInfo> tempList; 

    for (int i = 0; i < count; i++)
    {
        void* player = *(void**)(itemsArray + 0x20 + i * 0x8);
        if (!player) continue;
        if (player == (void*)localPlayer) continue; 

        PlayerInfo info{};
        info.isDead = *(bool*)((uintptr_t)player + 0x428);
        info.health = *(float*)((uintptr_t)player + 0x14C);
        info.armor = *(float*)((uintptr_t)player + 0x140);

        info.worldPos = GetPosition(player);

        tempList.push_back(info);
    }

    { 
        std::lock_guard<std::mutex> lock(Esp::playersMutex);
        Esp::players = std::move(tempList);
    }

    return oFpsPlayerUpdate(__this, method);
}

