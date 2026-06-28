#include "AppWindow.h"
#include "SwapChain.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include <Windows.h>

#include <cstdlib>
#include <ctime>



__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	float m_angle;
};

AppWindow::AppWindow()
{
}

void AppWindow::updateQuadPosition()
{
	constant cc;
	float deltaTime = static_cast<float>(EngineTime::getDeltaTime());

	m_angle += 1.57f * deltaTime;
	cc.m_angle = m_angle;


	

	Matrix4x4 temp;

	m_delta_scale += EngineTime::getDeltaTime() / 0.5f;

	
	cc.m_world.setIdentity();

	/*temp.setIdentity();
	temp.setRotationZ(15);
	cc.m_world *= temp;


	temp.setIdentity();
	temp.setRotationY(15);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(5);
	cc.m_world *= temp;*/

	m_delta_pos += speed * deltaTime;

	

	//Answer for making a plane from a cube #5
	/*if (m_delta_pos < 1.0f)
	{
		temp.setIdentity();
		temp.setScale(Vector3D::lerp(Vector3D(1, 1, 1), Vector3D(4, 0.25, 0), m_delta_pos));
		cc.m_world *= temp;
	}
	else {
		temp.setIdentity();
		temp.setScale(Vector3D::lerp(Vector3D(1, 1, 1), Vector3D(4, 0.25, 0), 1));
		cc.m_world *= temp;
	}*/

	
	/*m_delta_pos += speed * deltaTime;

	if (m_delta_pos > 1.0f)
	{
		m_delta_pos = 1.0f;
		speed = -speed;
	}
	else if (m_delta_pos < 0.0f)
	{
		m_delta_pos = 0.0f;
		speed = -speed;
	}

	
	temp.setIdentity();
	temp.setScale(Vector3D::lerp(Vector3D(1, 1, 1), Vector3D(0.25, 0.25, 0.25), m_delta_pos));
	cc.m_world *= temp;


	temp.setIdentity();
	temp.setTranslation(Vector3D::lerp(Vector3D(1, 1, 0), Vector3D(-1, -1, 0), m_delta_pos));
	cc.m_world *= temp;*/


	
	cc.m_view.setIdentity();

	//temp.setIdentity();
	//temp.setTranslation(Vector3D(0.0f, -0.01f, 1.0f));
	//cc.m_view *= temp;

	//temp.setIdentity();
	//temp.setRotationY(10);
	//cc.m_view *= temp;
	


	float aspect = (float)(this->getClientWindowRect().right - this->getClientWindowRect().left) /
		(float)(this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	cc.m_proj.setOrthoLH(
		2.0f * aspect,
		2.0f,
		-4.0f,
		4.0f
	);
	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	srand((unsigned int)time(nullptr));
	
    
	Window::onCreate();
	//GraphicsEngine::get()->init();
	GraphicsEngine::get()->initialize();
	
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	

	std::vector<Vector3D> pos;
	std::vector<Vector3D> cols;
	pos.push_back({ -0.1f, -0.1f, 0.0f });
	cols.push_back({ 0, 1, 0 });
	pos.push_back({ -0.1f, 0.1f,0.0f });
	cols.push_back({ 0,1,0 });
	pos.push_back({ 0.1f, -0.1f,0.0f });
	cols.push_back({ 0,1,0 });
	pos.push_back({ 0.1f,0.1f,0.0f });
	cols.push_back({ 0,1,0 });
	quadList.push_back(new Quads(pos, cols));
	pos.clear();
	cols.clear();

	
	cubeWork = new Cube();
	cubeList.push_back(cubeWork);
	//Answer for #4 render 50 random cubes
	/*for (int i = 0; i < 50; i++)
	{
		float x = ((float)rand() / RAND_MAX) * 2.0f - 1.0f; 
		float y = ((float)rand() / RAND_MAX) * 2.0f - 1.0f; 
		float z = ((float)rand() / RAND_MAX) * 2.0f - 1.0f; 

		Cube* cube = new Cube(x, y, z);
		cubeList.push_back(cube);
	}*/

	constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));

	

}

void AppWindow::onUpdate()
{
	if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
	{
		PostMessage(m_hwnd, WM_CLOSE, 0, 0);
	}


	Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,0,0.3,0.5,1);


	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	
	
	

	updateQuadPosition();
	
	
	//relevant to draws
	
	/*for (Quads* q : quadList) {
		q->setConstantBuffer(m_cb);
		q->draw();
	}*/
	cubeWork->setConstantBuffer(m_cb);
	cubeWork->draw();

	/*for (Cube* c : cubeList) {
		c->setConstantBuffer(m_cb);
		c->draw();
	}*/
	m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{
	for (Quads* q : quadList) {
		q->release();
	}
	for (Cube* c : cubeList) {
		c->release();
	}

	m_cb->Release();
	Window::onDestroy();
	m_swap_chain->release();
	GraphicsEngine::get()->destroy();


}
