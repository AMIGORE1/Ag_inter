#include "menu.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "core/global/config.h"
#include "havoc/hooks/plr_update/plr_update.h"
#include "../havoc/hooks/bone_esp/bone_esp.h"

void Render()
{
    if (ImGui::BeginTabBar("MyTabBar"))
    {
        if (ImGui::BeginTabItem("Weapon"))
        {
            ImGui::Text("Weapon Modifications");
            ImGui::Separator();

            ImGui::Checkbox("No Recoil", &config::NoRecoil);
            ImGui::Checkbox("Rapid Fire", &config::RapidFire);
            ImGui::Checkbox("Infinite Ammo", &config::InfAmmo);
            ImGui::Checkbox("Multi-Shot", &config::MultiShot);

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Checkbox("MEGA WEAPON MOD", &config::MegaWeaponMod);

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Aim"))
        {
            ImGui::Text("Aimbot Settings");
            ImGui::Separator();

            ImGui::Checkbox("Enable Aimbot", &config::Aimbot);

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Visuals"))
        {
            ImGui::Text("ESP & Visual Functions");
            ImGui::Checkbox("Esp", &config::showBox);
            ImGui::Separator();
            ImGui::Checkbox("Bone ESP", &BoneEsp::showBoneEsp);

            if (BoneEsp::showBoneEsp)
            {
                ImGui::Indent();
                ImGui::ColorEdit4("Bone Color", (float*)&BoneEsp::boneColor, ImGuiColorEditFlags_NoInputs);
                ImGui::ColorEdit4("Dead Bone Color", (float*)&BoneEsp::boneColorDead, ImGuiColorEditFlags_NoInputs);
                ImGui::SliderFloat("Bone Thickness", &BoneEsp::boneThickness, 0.5f, 4.0f, "%.1f");
                ImGui::Unindent();
            }

            if (ImGui::SliderFloat("Field of View", &config::fov, 40.0f, 180.0f, "%.0f"))
            {
                if (localPlayer != nullptr)
                {
                    localPlayer->CameraFov = config::fov;
                }
            }

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Movement"))
        {
            ImGui::Text("Movement Modifications");
            ImGui::Separator();

            ImGui::Checkbox("Speed Hack", &config::SpeedHack);
            ImGui::Checkbox("No Fall Damage", &config::NoFallDamage);
            ImGui::Checkbox("Spider-Man (Wall Run)", &config::SpiderMan);

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Checkbox("Fly Hack", &config::FlyHack);

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
}