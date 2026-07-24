#include "Cube.h"


Cube::Cube()
{
	this->vertex_list[0] = { Vector3D(-0.05f, -0.05f, -0.05f), Vector3D(1, 0, 0) };
	this->vertex_list[1] = { Vector3D(-0.05f, 0.05f,-0.05f), Vector3D(0,1,0) };
	this->vertex_list[2] = { Vector3D(0.05f, 0.05f,-0.05f), Vector3D(0,1,0) };
	this->vertex_list[3] = { Vector3D(0.05f,-0.05f,-0.05f), Vector3D(0,0,1) };
	this->vertex_list[4] = { Vector3D(0.05f,-0.05f, 0.05f), Vector3D(1,0,1) };
	this->vertex_list[5] = { Vector3D(0.05f, 0.05f, 0.05f), Vector3D(0,1,1) };
	this->vertex_list[6] = { Vector3D(-0.05f, 0.05f, 0.05f), Vector3D(0,0,0) };
	this->vertex_list[7] = { Vector3D(-0.05f,-0.05f, 0.05f), Vector3D(1,1,0) };
	this->init();
}

Cube::Cube(std::vector<Vector3D> pos, std::vector<Vector3D> cols)
{
	this->vertex_list[0] = { pos[0],    cols[0] };
	this->vertex_list[1] = { pos[1],    cols[1] };
	this->vertex_list[2] = { pos[2],    cols[2] };
	this->vertex_list[3] = { pos[3],    cols[3] };
	this->vertex_list[4] = { pos[4],    cols[4] };
	this->vertex_list[5] = { pos[5],    cols[5] };
	this->vertex_list[6] = { pos[6],    cols[6] };
	this->vertex_list[7] = { pos[7],    cols[7] };
	
	this->init();
}

//Cube::Cube(std::vector<Vector3D> pos, std::vector<Vector3D> pos2, std::vector<Vector3D> cols)
//{
//	this->vertex_list[0] = { pos[0], pos2[0],    cols[0]};
//	this->vertex_list[1] = { pos[1], pos2[1],    cols[1] };
//	this->vertex_list[2] = { pos[2], pos2[2],    cols[2] };
//	this->vertex_list[3] = { pos[3], pos2[3],    cols[3] };
//	this->init();
//}


Cube::Cube(float x, float y, float z)
{
	this->vertex_list[0] = { Vector3D(-0.05f + x, -0.05f + y, -0.05f + z), Vector3D(1, 0, 0) };
	this->vertex_list[1] = { Vector3D(-0.05f + x, 0.05f + y,-0.05f + z), Vector3D(0,1,0) };
	this->vertex_list[2] = { Vector3D(0.05f + x, 0.05f + y,-0.05f + z), Vector3D(0,1,0) };
	this->vertex_list[3] = { Vector3D(0.05f + x,-0.05f + y,-0.05f + z), Vector3D(0,0,1) };
	this->vertex_list[4] = { Vector3D(0.05f + x,-0.05f + y, 0.05f + z), Vector3D(1,0,1) };
	this->vertex_list[5] = { Vector3D(0.05f + x, 0.05f + y, 0.05f + z), Vector3D(0,1,1) };
	this->vertex_list[6] = { Vector3D(-0.05f + x, 0.05f + y, 0.05f + z), Vector3D(0,0,0) };
	this->vertex_list[7] = { Vector3D(-0.05f + x,-0.05f + y, 0.05f + z), Vector3D(1,1,0) };
	this->init();
}

void Cube::init()
{
	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,      //FIRST TRIANGLE
		2,3,0,      //SECOND TRIANGLE

		//BACK SIDE
		4,5,6,
		6,7,4,

		//TOP SIDE
		1,6,5,
		5,2,1,

		//BOTTOM SIDE
		7,0,3,
		3,4,7,

		//RIGHT SIDE
		3,2,5,
		5,4,3,

		//LEFT SIDE
		7,6,1,
		1,0,7
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

void Cube::draw()
{
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0,0);
}

void Cube::setConstantBuffer(ConstantBufferPtr  cb)
{

		GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, cb);
		GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, cb);
	
	
}



void Cube::release()
{

}
