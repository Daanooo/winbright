#include <iostream>
#include <vector>
#include <Windows.h>
#include <d3d9.h>
#include <highlevelmonitorconfigurationapi.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dxva2.lib")

IDirect3D9* setupDirect3D()
{
    IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if (!pD3D) {
        std::cerr << "Error creating IDirect3D9 object" << std::endl;
    }

    return pD3D;
}

IDirect3DDevice9* setupD3DDevice(IDirect3D9* pD3D)
{
    D3DPRESENT_PARAMETERS d3dpp{ };
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

    IDirect3DDevice9* device{ nullptr };

    if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetDesktopWindow(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &device))) {
        std::cerr << "Error creating IDirect3DDevice9 object" << std::endl;
        pD3D->Release();
    }

    return device;
}

int main()
{
    // Setup Direct3D
    IDirect3D9* pD3D{ setupDirect3D()};

    // Setup Direct3D device
    IDirect3DDevice9* device{ setupD3DDevice(pD3D) };

    DWORD monitorCount{ 0 };
    GetNumberOfPhysicalMonitorsFromIDirect3DDevice9(device, &monitorCount);

    std::vector<PHYSICAL_MONITOR> monitors(monitorCount);
    GetPhysicalMonitorsFromIDirect3DDevice9(device, monitorCount, monitors.data());
    HANDLE monitorHandle = monitors[0].hPhysicalMonitor;

    DWORD minBright{ 0 };
    DWORD maxBright{ 0 };
    DWORD currentBright{ 0 };
    GetMonitorBrightness(monitorHandle, &minBright, &currentBright, &maxBright);

    DWORD capabilities{ 0 };
    DWORD supportedColorTemps{ 0 };
    GetMonitorCapabilities(monitorHandle, &capabilities, &supportedColorTemps);

    SetMonitorBrightness(monitorHandle, 35);

    device->Release();
    pD3D->Release();

    return 0;
}
