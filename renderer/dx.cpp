#include "dx.h"

void DX::initialize()
{
    HWND hWnd = window.gethWnd();
    DXGI_SWAP_CHAIN_DESC scd;

    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    scd.BufferCount = 1;                                    
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      
    scd.OutputWindow = hWnd;                                
    scd.SampleDesc.Count = 4;                               
    scd.Windowed = TRUE;                                    

    // create a device, device context and swap chain using the information in the scd struct
    D3D11CreateDeviceAndSwapChain(NULL, //DXGI decides adapter
        D3D_DRIVER_TYPE_HARDWARE, // D11 works on hardware
        NULL, //it is used with D3D_DRIVER_TYPE_SOFTWARE (if DriverType is selected that)
        NULL, // D3D11_CREATE_DEVICE_BGRA_SUPPORT could be used for 2D library
        NULL,
        NULL,
        D3D11_SDK_VERSION,
        &scd,
        &swapchain,
        &device,
        NULL,
        &deviceContext);

    // get the address of the back buffer
    ID3D11Texture2D* pBackBuffer;
    swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    // use the back buffer address to create the render target
    device->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
    pBackBuffer->Release();

    // set the render target as the back buffer
    deviceContext->OMSetRenderTargets(1, &backbuffer, NULL);

    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = window.getWidth();
    viewport.Height = window.getHeight();

    deviceContext->RSSetViewports(1, &viewport);
}

DX::DX(Window window) : window(window)
{
    initialize();
}

DX::~DX()
{
	swapchain->Release();
	device->Release();
	deviceContext->Release();
	backbuffer->Release();
}

void DX::begin()
{
    float color[] = { 0.0f, 0.2f, 0.4f, 1.0f };
    deviceContext->ClearRenderTargetView(backbuffer, color);
}

void DX::end()
{
    swapchain->Present(0, 0);
}
