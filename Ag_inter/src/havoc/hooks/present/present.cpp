#include "present.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "menu/menu.h"
#include "../w2screen/w2screen.h"

PresentFn oPresent = nullptr;
bool Initialized = false;
bool showMenu = true;
HWND window = nullptr;
WNDPROC oWndProc = nullptr;

ID3D11Device* pDevice = nullptr;
ID3D11DeviceContext* pContext = nullptr;
ID3D11RenderTargetView* mainRenderTargetView = nullptr;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

void SetupImGuiStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowPadding = ImVec2(20.0f, 20.0f);
    style.WindowRounding = 12.0f;
    style.ChildRounding = 10.0f;
    style.FramePadding = ImVec2(12.0f, 8.0f);
    style.FrameRounding = 8.0f;
    style.ItemSpacing = ImVec2(10.0f, 10.0f);
    style.ScrollbarSize = 12.0f;
    style.GrabRounding = 8.0f;
    style.TabRounding = 8.0f;
    style.WindowBorderSize = 0.0f;
    style.ChildBorderSize = 1.0f;

    ImVec4 colorText = ImVec4(0.15f, 0.10f, 0.08f, 1.00f);
    ImVec4 colorBg = ImVec4(0.92f, 0.89f, 0.85f, 1.00f);
    ImVec4 colorAccent = ImVec4(0.45f, 0.30f, 0.20f, 1.00f);
    ImVec4 colorHover = ImVec4(0.55f, 0.40f, 0.30f, 1.00f);

    style.Colors[ImGuiCol_Text] = colorText;
    style.Colors[ImGuiCol_WindowBg] = colorBg;
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.88f, 0.85f, 0.80f, 1.00f);
    style.Colors[ImGuiCol_PopupBg] = colorBg;
    style.Colors[ImGuiCol_Border] = ImVec4(0.75f, 0.70f, 0.65f, 0.40f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.85f, 0.82f, 0.77f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.80f, 0.75f, 0.70f, 1.00f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.75f, 0.70f, 0.65f, 1.00f);
    style.Colors[ImGuiCol_CheckMark] = colorAccent;
    style.Colors[ImGuiCol_SliderGrab] = colorAccent;
    style.Colors[ImGuiCol_SliderGrabActive] = colorHover;
    style.Colors[ImGuiCol_Button] = ImVec4(0.85f, 0.80f, 0.75f, 1.00f);
    style.Colors[ImGuiCol_ButtonHovered] = colorHover;
    style.Colors[ImGuiCol_ButtonActive] = colorAccent;
    style.Colors[ImGuiCol_Header] = ImVec4(0.85f, 0.80f, 0.75f, 1.00f);
    style.Colors[ImGuiCol_HeaderHovered] = colorHover;
    style.Colors[ImGuiCol_HeaderActive] = colorAccent;
    style.Colors[ImGuiCol_Tab] = ImVec4(0.85f, 0.80f, 0.75f, 1.00f);
    style.Colors[ImGuiCol_TabHovered] = colorHover;
    style.Colors[ImGuiCol_TabActive] = colorAccent;
    style.Colors[ImGuiCol_Separator] = ImVec4(0.75f, 0.70f, 0.65f, 0.50f);
}

void InitImGui() {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(pDevice, pContext);
}

HRESULT initHkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT flags) {
    if (!Initialized) {
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice))) {
            pDevice->GetImmediateContext(&pContext);

            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            window = sd.OutputWindow;

            ID3D11Texture2D* pBackBuffer = nullptr;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            if (pBackBuffer) {
                pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
                pBackBuffer->Release();
            }

            oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);

            InitImGui();
            Initialized = true;

        }
    }

    return oPresent(pSwapChain, SyncInterval, flags);
}


HRESULT hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    static bool firstCall = true;

    if (firstCall)
    {
        firstCall = false;
        printf("[+] hkPresent hooked and called!\n");
    }

    if (!Initialized)
    {
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
        {
            pDevice->GetImmediateContext(&pContext);

            DXGI_SWAP_CHAIN_DESC desc;
            pSwapChain->GetDesc(&desc);
            window = desc.OutputWindow;

            ID3D11Texture2D* pBackBuffer = nullptr;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            if (pBackBuffer)
            {
                pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &mainRenderTargetView);
                pBackBuffer->Release();
            }

            oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);

            InitImGui();
            Initialized = true;

            printf("[+] ImGui initialized successfully!\n");
        }
        else
        {
            printf("[-] Failed to get D3D11 Device!\n");
        }
    }
    if (Initialized)
    {
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        SetupImGuiStyle();

        if (showMenu)
        {
            ImGui::SetNextWindowSize(ImVec2(600, 520), ImGuiCond_FirstUseEver);
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
            ImGui::Begin("Agyzak", &showMenu, window_flags);
            Render();
            ImGui::End();
        }

        Esp::Draw();

        ImGui::Render();
        pContext->OMSetRenderTargets(1, &mainRenderTargetView, nullptr);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }
    return oPresent(pSwapChain, SyncInterval, Flags);
}