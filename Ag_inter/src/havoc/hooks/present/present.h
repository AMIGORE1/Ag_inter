#pragma once
#include <windows.h>
#include <d3d11.h>
#include <cstdio>


typedef HRESULT(__fastcall* PresentFn)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT flags);
extern PresentFn oPresent;

HRESULT hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT flags);