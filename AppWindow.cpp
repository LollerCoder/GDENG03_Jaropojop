#include "AppWindow.h"
#include "SwapChain.h"
#include <Windows.h>

__declspec(align(16))
struct constant
{
	float m_angle;
};

AppWindow::AppWindow()
{
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

	std::vector<vec3> pos;
	std::vector<vec3>pos1;
	std::vector<vec3> cols;
	
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
	Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,0,0.3,0.5,1);


	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	unsigned long new_time = 0;
	if (m_old_time)
		new_time = ::GetTickCount() - m_old_time;
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();
	m_angle += 1.57f * m_delta_time;
	constant cc;
	cc.m_angle = m_angle;

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
	
	
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

	Window::onDestroy();
	m_swap_chain->release();
	GraphicsEngine::get()->destroy();


}
