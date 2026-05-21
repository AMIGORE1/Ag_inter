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

        float fx = feet.x;
        float fy = screenH - feet.y;
        float hx = head.x;
        float hy = screenH - head.y;

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

            float hpPercent = p.health / 100.f;
            if (hpPercent < 0.f) hpPercent = 0.f;
            if (hpPercent > 1.f) hpPercent = 1.f;

            float filledH = (bot - top) * hpPercent;

            float barRight = left - 3.f;
            float barLeft = barRight - 3.f;

            drawList->AddRectFilled(
                ImVec2(barLeft, top),
                ImVec2(barRight, bot),
                IM_COL32(0, 0, 0, 160)
            );

            float hue = hpPercent * 120.f / 360.f;
            float h = hue * 6.f;
            int   i = (int)h;
            float f = h - i;
            float q = 1.f - f;
            float t2 = f;

            float fr, fg, fb;
            switch (i % 6)
            {
            case 0: fr = 1.f; fg = t2;  fb = 0.f; break;
            case 1: fr = q;   fg = 1.f; fb = 0.f; break;
            case 2: fr = 0.f; fg = 1.f; fb = t2;  break;
            default:fr = 0.f; fg = 1.f; fb = 0.f; break;
            }

            int r = (int)(fr * 255);
            int g = (int)(fg * 255);
            int b = (int)(fb * 255);

            drawList->AddRectFilled(
                ImVec2(barLeft, bot - filledH),
                ImVec2(barRight, bot),
                IM_COL32(r, g, b, 255)
            );
        }
    }
}