#include "AppWindow.h"
#include "SwapChain.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include <Windows.h>





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


	m_delta_pos += EngineTime::getDeltaTime() * 1.0f;

	if (m_delta_pos > 1.0f)
		m_delta_pos = 0.0f;

	Matrix4x4 temp;

	m_delta_scale += EngineTime::getDeltaTime() / 0.5f;

	//cc.m_world.setTranslation(Vector3D(0, 0, 0));
	//cc.m_world.setTranslation(Vector3D::lerp(Vector3D(-2, -2, 0), Vector3D(2,2,0),m_delta_pos));
	cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(2, 2, 0), (sin(m_delta_scale) + 1.0f) / 2.0f));
	temp.setTranslation(Vector3D::lerp(Vector3D(-2, -2, 0), Vector3D(2, 2, 0), m_delta_pos));
	cc.m_world *= temp;
	cc.m_view.setIdentity();
	//cc.m_proj.setIdentity();
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
	
	
    
	Window::onCreate();
	//GraphicsEngine::get()->init();
	GraphicsEngine::get()->initialize();
	
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	std::vector<Vector3D> pos;
	std::vector<Vector3D>pos1;
	std::vector<Vector3D> cols;
	
	pos.push_back({ -0.1f, -0.1f, 0.0f });
	pos1.push_back({ -0.5f, -0.5f, 0.0f });
	cols.push_back({ 0, 1, 0 });

	pos.push_back({ -0.1f, 0.1f,0.0f });
	pos1.push_back({ -0.5f, 0.5f,0.0f });
	cols.push_back({ 0,1,0 });

	pos.push_back({ 0.1f, -0.1f,0.0f });
	pos1.push_back({ 0.5f, -0.5f,0.0f });
	cols.push_back({ 0,1,0 });

	pos.push_back({ 0.1f,0.1f,0.0f });
	pos1.push_back({ 0.5f, 0.5f,0.0f });
	cols.push_back({ 0,1,0 });

	quadList.push_back(new Quads(pos, pos1, cols));
	pos.clear();
	pos1.clear();
	cols.clear();

	

	
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
	
	for (Quads* q : quadList) {
		q->setConstantBuffer(m_cb);
		q->draw();
	}
	m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{
	for (Quads* q : quadList) {
		q->release();
	}
	m_cb->Release();
	Window::onDestroy();
	m_swap_chain->release();
	GraphicsEngine::get()->destroy();


}
