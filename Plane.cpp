#include "Plane.h"


Plane::Plane()
{
	vertex_list[0] = { Vector3D(-0.5f, 0.0f, -0.5f),  Vector3D(1.0f, 0.0f, 0.0f) };
	vertex_list[1] = { Vector3D(-0.5f, 0.0f,  0.5f), Vector3D(1.0f, 0.0f, 0.0f) };
	vertex_list[2] = { Vector3D(0.5f, 0.0f,  0.5f),  Vector3D(1.0f, 0.0f, 0.0f) };
	vertex_list[3] = { Vector3D(0.5f, 0.0f, -0.5f),  Vector3D(1.0f, 0.0f, 0.0f) };
	this->init();
}

Plane::Plane(std::vector<Vector3D> pos, std::vector<Vector3D> cols)
{
	this->vertex_list[0] = { pos[0],    cols[0] };
	this->vertex_list[1] = { pos[1],    cols[1] };
	this->vertex_list[2] = { pos[2],    cols[2] };
	this->vertex_list[3] = { pos[3],    cols[3] };
	
	this->init();
}

//Plane::Plane(std::vector<Vector3D> pos, std::vector<Vector3D> pos2, std::vector<Vector3D> cols)
//{
//	this->vertex_list[0] = { pos[0], pos2[0],    cols[0]};
//	this->vertex_list[1] = { pos[1], pos2[1],    cols[1] };
//	this->vertex_list[2] = { pos[2], pos2[2],    cols[2] };
//	this->vertex_list[3] = { pos[3], pos2[3],    cols[3] };
//	this->init();
//}


Plane::Plane(float x, float y, float z)
{
	this->vertex_list[0] = { Vector3D(-0.05f + x, -0.05f + y, -0.05f + z), Vector3D(1, 0, 0) };
	this->vertex_list[1] = { Vector3D(-0.05f + x, 0.05f + y,-0.05f + z), Vector3D(0,1,0) };
	this->vertex_list[2] = { Vector3D(0.05f + x, 0.05f + y,-0.05f + z), Vector3D(0,1,0) };
	this->vertex_list[3] = { Vector3D(0.05f + x,-0.05f + y,-0.05f + z), Vector3D(0,0,1) };
	
	this->init();
}

void Plane::init()
{
	unsigned int index_list[] =
	{
		0, 1, 2,
		0, 2, 3
	};


	UINT size_index_list = ARRAYSIZE(index_list);
	m_ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(index_list, size_index_list);

	UINT size_list = ARRAYSIZE(this->vertex_list);
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);
	m_vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	

	
	

	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);


	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();
}

void Plane::draw()
{
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void Plane::setConstantBuffer(ConstantBuffer* cb)
{

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, cb);


}



void Plane::release()
{
}
