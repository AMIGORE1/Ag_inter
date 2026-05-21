// -------------------------------------------------------
//  plr_update.cpp — ЗМІНЕНИЙ hFpsPlayerUpdate
//  Додаємо збір animatorPtr для BoneEsp
//  Animator знаходиться як компонент гравця.
//  Зазвичай в il2cpp-іграх Animator доступний через
//  поле-вказівник в об'єкті гравця. Тут він береться
//  зміщенням 0x368 (підбери під свій білд через dumper).
// -------------------------------------------------------

#include "plr_update.h"
#include "esp.h"           // замість повного визначення
#include "bone_esp.h"

Player* localPlayer = nullptr;

// Офсет до поля Animator* всередині FPSPlayer об'єкту.
// Знайди через Il2CppDumper / ReClass / логування.
static constexpr uintptr_t ANIMATOR_OFFSET = 0x278;

void __fastcall hFpsPlayerUpdate(void* __this, const void* method)
{
    localPlayer = reinterpret_cast<Player*>(__this);

    uintptr_t listPtr = *(uintptr_t*)((uintptr_t)__this + 0x598);
    if (!listPtr) return oFpsPlayerUpdate(__this, method);

    int count = *(int*)(listPtr + 0x18);
    if (count <= 0 || count > 64) return oFpsPlayerUpdate(__this, method);

    uintptr_t itemsArray = *(uintptr_t*)(listPtr + 0x10);
    if (!itemsArray) return oFpsPlayerUpdate(__this, method);

    std::vector<PlayerInfo>    tempList;
    std::vector<BonePlayerInfo> boneList;   // <-- новий список

    for (int i = 0; i < count; i++)
    {
        void* player = *(void**)(itemsArray + 0x20 + i * 0x8);
        if (!player) continue;
        if (player == (void*)localPlayer) continue;

        bool isDead = *(bool*)((uintptr_t)player + 0x428);

        // --- звичайний ESP ---
        PlayerInfo info{};
        info.isDead = isDead;
        info.health = *(float*)((uintptr_t)player + 0x14C);
        info.armor = *(float*)((uintptr_t)player + 0x140);
        info.worldPos = GetPosition(player);
        tempList.push_back(info);

        // --- bone ESP: беремо Animator* ---
        void* animPtr = *(void**)((uintptr_t)player + ANIMATOR_OFFSET);
        BonePlayerInfo boneInfo{};
        boneInfo.animatorPtr = animPtr;
        boneInfo.isDead = isDead;
        boneList.push_back(boneInfo);
    }

    {
        std::lock_guard<std::mutex> lock(Esp::playersMutex);
        Esp::players = std::move(tempList);
    }
    {
        std::lock_guard<std::mutex> lock(BoneEsp::bonePlayersMutex);
        BoneEsp::bonePlayers = std::move(boneList);
    }

    return oFpsPlayerUpdate(__this, method);
}