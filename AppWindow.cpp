#include "AppWindow.h"
#include "SwapChain.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include <Windows.h>
#include "InputSystem.h"

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

void AppWindow::update()
{
	constant cc;
	float deltaTime = static_cast<float>(EngineTime::getDeltaTime());

	


	

	Matrix4x4 temp;


	
	cc.m_world.setIdentity();

	

	Matrix4x4 world_cam;

	world_cam.setIdentity();


	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	world_cam *= temp;

	Vector3D new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.3f);

	new_pos = new_pos + world_cam.getXDirection()*(m_rightward*0.3f);


	world_cam.setTranslation(new_pos);
	m_world_cam = world_cam;
	world_cam.inverse();

	
	cc.m_view = world_cam;


	float aspect = (float)(this->getClientWindowRect().right - this->getClientWindowRect().left) /
		(float)(this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	/*cc.m_proj.setOrthoLH(
		2.0f * aspect,
		2.0f,
		-4.0f,
		4.0f
	);*/

	cc.m_proj.setPerspectiveFovLH(1.57f,aspect,0.1f,100.0f);
	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	srand((unsigned int)time(nullptr));
	
    
	Window::onCreate();
	
	
	InputSystem::get()->addListener(this);
	InputSystem::get()->showCursor(false);

	//GraphicsEngine::get()->init();
	GraphicsEngine::get()->initialize();
	
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	m_world_cam.setTranslation(Vector3D(0, 0, -2));

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

	plane = new Plane();

	
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
	


	Window::onUpdate();
	InputSystem::get()->update();

	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,0,0.3,0.5,1);


	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	
	
	

	update();
	
	
	//relevant to draws
	
	/*for (Quads* q : quadList) {
		q->setConstantBuffer(m_cb);
		q->draw();
	}*/
	plane->setConstantBuffer(m_cb);
	plane->draw();
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

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);

}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
	if (key == 'W') {
		//m_rot_x += 0.707f * EngineTime::getDeltaTime();
		m_forward = 1.0f;
	}
	else if (key == 'S') {
		//m_rot_x -= 0.707f * EngineTime::getDeltaTime();
		m_forward = -1.0f;
	}

	if (key == 'A') {
		//m_rot_y += 0.707f * EngineTime::getDeltaTime();
		m_rightward = -1.0f;
	}
	else if (key == 'D') {
		//m_rot_y -= 0.707f * EngineTime::getDeltaTime();
		m_rightward = 1.0f;
	}
}

void AppWindow::onKeyUp(int key)
{
	m_forward = 0.0f;
	m_rightward = 0.0f;
}

void AppWindow::onMouseMove(const Point& mouse_pos)
{
	int width = (float)(this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height =	(float)(this->getClientWindowRect().bottom - this->getClientWindowRect().top);



	m_rot_x += (mouse_pos.m_y - (height/2.0f)) * EngineTime::getDeltaTime() * 0.1f;
	m_rot_y += (mouse_pos.m_x - (width / 2.0f)) * EngineTime::getDeltaTime() * 0.1f;



	InputSystem::get()->setCursorPosition(Point(width/2.0f,height/2.0f));
}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{
	m_scale_cube = 2.0f;
}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{
	m_scale_cube = 1.0f;
}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{
	m_scale_cube = 0.5f;
}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{
	m_scale_cube = 1.0f;
}
