#ifndef SHADERS_HPP
#define SHADERS_HPP

#include <d3d11.h>
#include <d3dcompiler.h>
#include <comdef.h>
#include <sstream>


#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

#include "StrException.hpp"
#include "Macros.hpp"

class Shaders
{
private:
	ID3D11VertexShader* pVertexShader[M_VERTEX_SHADER_COUNT];
	ID3D11InputLayout* pInputLayout[M_VERTEX_SHADER_COUNT];
	ID3D11GeometryShader* pGeometryShader[M_GEOMETRY_SHADER_COUNT];
	ID3D11PixelShader* pPixelShader[M_PIXEL_SHADER_COUNT];

	void CreateVertexShaders(ID3D11Device *device);
	void CreateGeometryShaders(ID3D11Device *device);
	void CreatePixelShaders(ID3D11Device *device);

public:
	Shaders();
	virtual ~Shaders();

	enum eVertexShader		: unsigned int { vshader_default = 0 };
	enum eGeometryShader	: unsigned int { gshader_default = 0 };
	enum ePixelShader		: unsigned int { pshader_default = 0 };

	void Init(ID3D11Device *device);

	ID3D11VertexShader* FetchVS(unsigned int id);
	ID3D11GeometryShader* FetchGS(unsigned int id);
	ID3D11PixelShader* FetchPS(unsigned int id);
};

#endif