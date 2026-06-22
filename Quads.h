#pragma once
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include <vector>


struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 color;
};

class Quads
{
public:
	Quads();
	Quads(std::vector<vec3> pos, std::vector<vec3> cols);
	void init();
	void draw();
	void release();

private:
	vertex m_list[4];
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;

};

