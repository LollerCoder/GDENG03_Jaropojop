#include "Quads.h"

Quads::Quads()
{
	this->m_list[0] = { -0.5f,-0.5f,0.0f,    0,1,0 };
	this->m_list[1] = { -0.5f, 0.5f,0.0f,    0,1,0 };
	this->m_list[2] = { 0.5f, -0.5f,0.0f,    0,1,0 };
	this->m_list[3] = { 0.5f,0.5f,0.0f,      0,1,0 };
	this->init();
}

Quads::Quads(std::vector<vec3> pos, std::vector<vec3> cols)
{
	this->m_list[0] = { pos[0],    cols[0]};
	this->m_list[1] = { pos[1],    cols[1] };
	this->m_list[2] = { pos[2],    cols[2] };
	this->m_list[3] = { pos[3],    cols[3] };
	this->init();
}

Quads::Quads(std::vector<vec3> pos, std::vector<vec3> pos2, std::vector<vec3> cols)
{
	this->m_list[0] = { pos[0], pos2[0],    cols[0]};
	this->m_list[1] = { pos[1], pos2[1],    cols[1] };
	this->m_list[2] = { pos[2], pos2[2],    cols[2] };
	this->m_list[3] = { pos[3], pos2[3],    cols[3] };
	this->init();
}


void Quads::init()
{
	


	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(this->m_list);



	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(m_list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);


	GraphicsEngine::get()->releaseCompiledShader();
}

void Quads::draw()
{
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

void Quads::setConstantBuffer(ConstantBuffer* cb)
{
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, cb);
}

void Quads::release()
{
	this->m_vb->Release();
	this->m_ps->Release();
	this->m_vs->Release();
}
