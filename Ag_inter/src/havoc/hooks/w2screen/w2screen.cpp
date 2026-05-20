#include "w2screen.h"

void* Esp::currentCamera = nullptr;

Vector3 __fastcall hWorldToScreenPoint(void* camera, Vector3 position, const void* method)
{
    if (camera)
        Esp::currentCamera = camera;
    return oWorldToScreenPoint(camera, position, method);
}

ImU32 Esp::ToU32(ImVec4 c)
{
    return IM_COL32(
        (int)(c.x * 255), (int)(c.y * 255),
        (int)(c.z * 255), (int)(c.w * 255)
    );
}

void Esp::Draw()
{
    if (!currentCamera || !oWorldToScreenPoint) return;

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    if (!drawList) return;

    ImGuiIO& io = ImGui::GetIO();
    float screenW = io.DisplaySize.x;
    float screenH = io.DisplaySize.y;

    std::lock_guard<std::mutex> lock(playersMutex);

    for (auto& p : players)
    {
        if (p.isDead && !showDeadPlayers) continue;

        Vector3 feet = oWorldToScreenPoint(currentCamera, p.worldPos, nullptr);
        Vector3 headWorld = { p.worldPos.x, p.worldPos.y + 1.8f, p.worldPos.z };
        Vector3 head = oWorldToScreenPoint(currentCamera, headWorld, nullptr);

        if (feet.z < 0.01f || head.z < 0.01f) continue; 
        printf("[ESP] feet screen=(%.1f, %.1f, %.1f) screenW=%.0f screenH=%.0f\n",
            feet.x, feet.y, feet.z, screenW, screenH);

        float fx = feet.x;
        float fy = feet.y;         
        float hx = head.x;
        float hy = head.y;

        float boxH = fy - hy;
        if (boxH < 5.f) continue;

        float boxW = std::max(boxH * 0.4f, 20.f); 
        float left = hx - boxW * 0.5f;
        float right = hx + boxW * 0.5f;
        float top = hy;
        float bot = fy;

        if (right < 0 || left > screenW || bot < 0 || top > screenH) continue;

        ImU32 col = p.isDead ? ToU32(deadColor) : ToU32(boxColor);

        if (config::showBox)
        {
            drawList->AddRect(
                ImVec2(left, top), ImVec2(right, bot),
                col, 0.f, 0, boxThickness
            );
        }
    }
}