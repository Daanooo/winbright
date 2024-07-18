#include <iostream>
#include <vector>
#include <Windows.h>
#include <d3d9.h>
#include <highlevelmonitorconfigurationapi.h>

#include "monitor.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dxva2.lib")

IDirect3D9* setupDirect3D() {
    IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if (!pD3D) {
        std::cerr << "Error creating IDirect3D9 object" << std::endl;
    }

    return pD3D;
}

IDirect3DDevice9* setupD3DDevice(IDirect3D9* pD3D) {
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

std::vector<Monitor> getMonitors(IDirect3DDevice9* device) {
    DWORD monitorCount{ 0 };
    GetNumberOfPhysicalMonitorsFromIDirect3DDevice9(device, &monitorCount);

    std::vector<PHYSICAL_MONITOR> physicalMonitors(monitorCount);
    GetPhysicalMonitorsFromIDirect3DDevice9(device, monitorCount, physicalMonitors.data());

    std::vector<Monitor> monitorObjects;
    for (int i = 0; i < monitorCount; i++) {
        HANDLE handle{ physicalMonitors[i].hPhysicalMonitor };
        Monitor monitor(handle);
        monitorObjects.push_back(monitor);
    }

    return monitorObjects;
}

int main(int argc, char* argv[]) {
    DWORD ulBrightness = strtoul(argv[1], nullptr, 10);

    // Setup Direct3D
    IDirect3D9* pD3D{ setupDirect3D()};

    // Setup Direct3D device
    IDirect3DDevice9* device{ setupD3DDevice(pD3D) };

    std::vector<Monitor> monitors{ getMonitors(device) };

    monitors[0].setBrightness(ulBrightness);

    device->Release();
    pD3D->Release();

    return 0;
}
