#include "Graphics.hpp"

void Graphics::CreateDirect3DContext(HWND *wndHandle)
{
	DXGI_SWAP_CHAIN_DESC scd = {};
	wchar_t err_msg[250];				// Temporary error handling method

	// fill the swap chain description struct
	scd.BufferCount = 1;									// one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		// use 32-bit color
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		// how swap chain is to be used
	scd.OutputWindow = *wndHandle;							// the window to be used
	scd.SampleDesc.Count = M_SAMPLE_COUNT;					// how many multisamples
	scd.Windowed = M_WINDOWED;								// windowed/full-screen mode

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
		if (!SUCCEEDED(hr))
		{
			_com_error err(hr);
			wcscpy_s(err_msg, L"Error at CreateDirect3DContext\nCreateTexture2D:\n");
			wcscat_s(err_msg, err.ErrorMessage());
			throw err_msg;
		}

		hr = device->CreateDepthStencilView(depthTexture2D, NULL, &depthStencilView);
		if (!SUCCEEDED(hr))
		{
			_com_error err(hr);
			wcscpy_s(err_msg, L"Error at CreateDirect3DContext\nCreateDepthStencilView:\n");
			wcscat_s(err_msg, err.ErrorMessage());
			throw err_msg;
		}

		// ========

		// set the render target as the back buffer
		deviceContext->OMSetRenderTargets(1, &backbufferRTV, depthStencilView);
	}
	else {
		
		_com_error err(hr);
		wcscpy_s(err_msg, L"Error at CreateDirect3DContext\nD3D11CreateDeviceAndSwapChain:\n");
		wcscat_s(err_msg, err.ErrorMessage());
		throw err_msg;
	}
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
}
