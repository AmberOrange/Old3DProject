#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <Windows.h>
#include <d3d11.h>
#pragma comment (lib, "d3d11.lib")

#include "StrException.hpp"
#include "Shaders.hpp"
#include "Macros.hpp"

class Graphics
{
private:
	// PRIVATE VARIABLES
	IDXGISwapChain *swapChain;
	ID3D11Device *device;
	ID3D11DeviceContext *deviceContext;
	ID3D11RenderTargetView* backbufferRTV;

	ID3D11Texture2D* depthTexture2D;
	ID3D11DepthStencilView* depthStencilView;

	Shaders shaders;
	// PRIVATE FUNCTIONS
	void CreateDirect3DContext(HWND *wndHandle);
	void SetViewport();
public:
	Graphics();
	virtual ~Graphics();

	void Init(HWND *wndHandle);

};

#endif