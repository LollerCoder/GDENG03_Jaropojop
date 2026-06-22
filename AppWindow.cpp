#include "AppWindow.h"
#include "SwapChain.h"



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
	std::vector<vec3> cols;
	
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

	pos.push_back({ -0.9f, 0.9f, 0.0f });
	cols.push_back({ 0,0,1 });

	pos.push_back({ -0.8f, 0.9f,0.0f });
	cols.push_back({ 0,0,1 });

	pos.push_back({ -0.9f,0.8f,0.0f });
	cols.push_back({ 0,0,1 });

	pos.push_back({ -0.8f, 0.8f,0.0f });
	cols.push_back({ 0,0,1 });

	quadList.push_back(new Quads(pos, cols));

	pos.clear();
	cols.clear();

	pos.push_back({ 0.9f, -0.9f, 0.0f });
	cols.push_back({ 1,0,0 });

	pos.push_back({ 0.8f, -0.9f,0.0f });
	cols.push_back({ 1,0,0 });

	pos.push_back({ 0.9f,-0.8f,0.0f });
	cols.push_back({ 1,0,0 });

	pos.push_back({ 0.8f, -0.8f,0.0f });
	cols.push_back({ 1,0,0 });

	quadList.push_back(new Quads(pos, cols));

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,0,0.3,0.5,1);


	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	
	//relevant to draws
	
	for (Quads* q : quadList) {
		q->draw();
	}
	m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{

	Window::onDestroy();
	m_swap_chain->release();
	GraphicsEngine::get()->destroy();


}
