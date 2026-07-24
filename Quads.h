#pragma once
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include <vector>
#include "ConstantBuffer.h"
#include "Vector3D.h"


struct vertex
{
	Vector3D position;
	
	Vector3D color;
};

class Quads
{
public:
	Quads();
	Quads(std::vector<Vector3D> pos, std::vector<Vector3D> cols);
	/*Quads(std::vector<Vector3D> pos, std::vector<Vector3D> pos2, std::vector<Vector3D> cols);*/

	void init();
	void draw();
	void setConstantBuffer(ConstantBufferPtr  cb);
	void release();

private:
	vertex m_list[4];
	VertexBufferPtr m_vb;
	VertexShaderPtr m_vs;
	PixelShaderPtr m_ps;
	
};

