#include "Shaders.hpp"

void Shaders::CreateVertexShaders(ID3D11Device * device)
{

	#pragma region vshader_default
	ID3DBlob* pVS = nullptr;
	ID3DBlob* err_blob = nullptr;
	HRESULT hr = D3DCompileFromFile(
		L"vshader_default.hlsl", // filename
		nullptr,		// optional macros
		nullptr,		// optional include files
		"main",			// entry point
		"vs_5_0",		// shader model (target)
		0,				// shader compile options			// here DEBUGGING OPTIONS
		0,				// effect compile options
		&pVS,			// double pointer to ID3DBlob		
		&err_blob		// pointer for Error Blob messages.
						// how to use the Error blob, see here
						// https://msdn.microsoft.com/en-us/library/windows/desktop/hh968107(v=vs.85).aspx
	);

	// Check if any errors occured during compilation
	if (FAILED(hr))
		throw StrException("Error at CreateVertexShaders\nD3DCompileFromFile:\n", hr, err_blob);

	hr = device->CreateVertexShader(pVS->GetBufferPointer(), pVS->GetBufferSize(), nullptr, &pVertexShader[vshader_default]);
	if (FAILED(hr))
		throw StrException("Error at CreateVertexShaders\nCreateVertexShader:\n", hr);

	//create input layout (verified using vertex shader)
	D3D11_INPUT_ELEMENT_DESC inputDesc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	hr = device->CreateInputLayout(inputDesc, ARRAYSIZE(inputDesc), pVS->GetBufferPointer(), pVS->GetBufferSize(), &pInputLayout[vshader_default]);
	if (FAILED(hr))
		throw StrException("Error at CreateVertexShaders\nCreateInputLayout:\n", hr);
	// we do not need anymore this COM object, so we release it.
	pVS->Release();
	#pragma endregion 

}

void Shaders::CreateGeometryShaders(ID3D11Device * device)
{
}

void Shaders::CreatePixelShaders(ID3D11Device * device)
{

	#pragma region pshader_default
	ID3DBlob* pPS = nullptr;
	ID3DBlob* err_blob = nullptr;
	HRESULT hr = D3DCompileFromFile(
		L"pshader_default.hlsl", // filename
		nullptr,		// optional macros
		nullptr,		// optional include files
		"main",			// entry point
		"ps_5_0",		// shader model (target)
		0,				// shader compile options
		0,				// effect compile options
		&pPS,			// double pointer to ID3DBlob		
		&err_blob		// pointer for Error Blob messages.
						// how to use the Error blob, see here
						// https://msdn.microsoft.com/en-us/library/windows/desktop/hh968107(v=vs.85).aspx
	);

	if (FAILED(hr))
		throw StrException("Error at CreatePixelShaders\nD3DCompileFromFile:\n", hr, err_blob);

	hr = device->CreatePixelShader(pPS->GetBufferPointer(), pPS->GetBufferSize(), nullptr, &pPixelShader[pshader_default]);
	if (FAILED(hr))
		throw StrException("Error at CreatePixelShaders\nCreatePixelShader:\n", hr);

	// we do not need anymore this COM object, so we release it.
	pPS->Release();
	#pragma endregion

}

Shaders::Shaders()
{
}

Shaders::~Shaders()
{
}

void Shaders::Init(ID3D11Device * device)
{
	this->CreateVertexShaders(device);
	this->CreateGeometryShaders(device);
	this->CreatePixelShaders(device);
}

ID3D11VertexShader * Shaders::FetchVS(unsigned int id)
{
	return pVertexShader[id];
}

ID3D11GeometryShader * Shaders::FetchGS(unsigned int id)
{
	return pGeometryShader[id];
}

ID3D11PixelShader * Shaders::FetchPS(unsigned int id)
{
	return pPixelShader[id];
}
