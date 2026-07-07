#pragma once
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include <vector>
#include "ConstantBuffer.h"
#include "Vector3D.h"
#include "Quads.h"
#include "IndexBuffer.h"





class Cube
{
public:
	Cube();
	Cube(std::vector<Vector3D> pos, std::vector<Vector3D> cols);
	/*Cube(std::vector<Vector3D> pos, std::vector<Vector3D> pos2, std::vector<Vector3D> cols);*/
	Cube(float x,float y,float z);
	void init();
	void draw();
	void setConstantBuffer(ConstantBuffer* cb);

	void release();

private:
	friend class Quads;
	vertex vertex_list[8];
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	IndexBuffer* m_ib;


	

};

