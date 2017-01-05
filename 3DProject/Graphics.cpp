#include "Graphics.hpp"

void Graphics::CreateDirect3DContext(HWND *wndHandle)
{
	DXGI_SWAP_CHAIN_DESC scd = {};
	char err_msg[250];				// Temporary error handling method, make something better later

	// fill the swap chain description struct
	scd.BufferCount = 1;									// one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		// use 32-bit color
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		// how swap chain is to be used
	scd.OutputWindow = *wndHandle;							// the window to be used
	scd.SampleDesc.Count = M_SAMPLE_COUNT;					// how many multisamples
	scd.Windowed = M_WINDOWED;								// windowed/full-screen mode

	unsigned int hello = Shaders::eVertexShader::vshader_default;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&swapChain,
		&device,
		NULL,
		&deviceContext);

	if (SUCCEEDED(hr))
	{
		// get the address of the back buffer
		ID3D11Texture2D* pBackBuffer = nullptr;
		swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		// use the back buffer address to create the render target
		device->CreateRenderTargetView(pBackBuffer, NULL, &backbufferRTV);
		pBackBuffer->Release();

		// DEPTH BUFFER =====
		D3D11_TEXTURE2D_DESC depthStencilDesc;

		depthStencilDesc.Width = M_WIDTH;
		depthStencilDesc.Height = M_HEIGHT;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthStencilDesc.SampleDesc.Count = M_SAMPLE_COUNT;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;

		hr = device->CreateTexture2D(&depthStencilDesc, NULL, &depthTexture2D);
		if (FAILED(hr))
			throw StrException("Error at CreateDirect3DContext\nCreateTexture2D:\n", hr);

		hr = device->CreateDepthStencilView(depthTexture2D, NULL, &depthStencilView);
		if (FAILED(hr))
			throw StrException("Error at CreateDirect3DContext\nCreateDepthStencilView:\n", hr);

		// ========

		// set the render target as the back buffer
		deviceContext->OMSetRenderTargets(1, &backbufferRTV, depthStencilView);
	}
	else throw StrException("Error at CreateDirect3DContext\nD3D11CreateDeviceAndSwapChain:\n", hr);
}

// Sets the viewport to the rasterizer
// TODO: Any way to throw errors?
void Graphics::SetViewport()
{
	D3D11_VIEWPORT vp;
	vp.Width = (float)M_WIDTH;
	vp.Height = (float)M_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	deviceContext->RSSetViewports(1, &vp);	// Bind an array of viewports to the rasterizer stage of the pipeline.
												// NumViewports - Number of viewports to bind
												// *pViewports  - Array of viewports to bind
}

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

void Graphics::Init(HWND *wndHandle)
{
	this->CreateDirect3DContext(wndHandle);
	this->SetViewport();
	this->shaders.Init(this->device);
}
