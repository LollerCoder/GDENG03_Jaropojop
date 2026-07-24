#include "Quads.h"

Quads::Quads()
{
	this->m_list[0] = { Vector3D( - 0.5f,-0.5f,0.0f),    Vector3D(0,1,0)};
	this->m_list[1] = { Vector3D( - 0.5f, 0.5f,0.0f),    Vector3D(0,1,0)};
	this->m_list[2] = { Vector3D(0.5f, -0.5f,0.0f),    Vector3D(0,1,0) };
	this->m_list[3] = { Vector3D(0.5f,0.5f,0.0f),      Vector3D(0,1,0) };
	this->init();
}

Quads::Quads(std::vector<Vector3D> pos, std::vector<Vector3D> cols)
{
	this->m_list[0] = { pos[0],    cols[0]};
	this->m_list[1] = { pos[1],    cols[1] };
	this->m_list[2] = { pos[2],    cols[2] };
	this->m_list[3] = { pos[3],    cols[3] };
	this->init();
}

//Quads::Quads(std::vector<Vector3D> pos, std::vector<Vector3D> pos2, std::vector<Vector3D> cols)
//{
//	this->m_list[0] = { pos[0], pos2[0],    cols[0]};
//	this->m_list[1] = { pos[1], pos2[1],    cols[1] };
//	this->m_list[2] = { pos[2], pos2[2],    cols[2] };
//	this->m_list[3] = { pos[3], pos2[3],    cols[3] };
//	this->init();
//}


void Quads::init()
{
	

	UINT size_list = ARRAYSIZE(this->m_list);
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);

	m_vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(m_list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	
	

	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);


	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();
}

void Quads::draw()
{
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

void Quads::setConstantBuffer(ConstantBuffer* cb)
{
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, cb);
}

void Quads::release()
{
	
}
