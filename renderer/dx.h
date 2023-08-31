#ifndef DX_H
#define DX_H

#include <d3d11.h>
#include "window.h"

class DX {
private:
	IDXGISwapChain* swapchain;
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	ID3D11RenderTargetView* backbuffer;

	Window window;
private:
	void initialize();

public:

	DX(Window window);
	~DX();

	void begin();
	void end();
};

#endif // !DX_H
