#include "AppWindow.h"
#include "SwapChain.h"
//#include "Sound.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 color;
};

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	//SoundEngine stuff
	/*wchar_t path[MAX_PATH];
	GetCurrentDirectoryW(MAX_PATH, path);
	OutputDebugStringW(path);
	OutputDebugStringW(L"\n");

	OutputDebugStringA("START\n");
	if (!m_soundEngine.init())
        return;

    if (!m_chime.load(
        m_soundEngine.getAudioEngine(),
        L"lion.wav"))
        return;
	m_chime.play();*/
    
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	vertex list[] = {
		//triangle
		/*{-0.5f,-0.5f,0.0f},
		{0.0f, 0.5f,0.0f},
		{0.5f,-0.5f,0.0f}*/

		//square with triangle list
		/*{-0.5f,-0.5f,0.0f},
		{-0.5f, 0.5f,0.0f},
		{0.5f,0.5f,0.0f},

		{ 0.5f,0.5f,0.0f },
		{0.5f, -0.5f,0.0f},
		{-0.5f,-0.5f,0.0f}*/

		//square but with triangle strip
		{-0.5f,-0.5f,0.0f,    1,0,0},
		{-0.5f, 0.5f,0.0f,    0,1,0},
		{0.5f, -0.5f,0.0f,    1,0,1},
		{0.5f,0.5f,0.0f,      0,0,1}
	};


	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl","vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(list, sizeof(vertex), size_list,shader_byte_code,size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	

	GraphicsEngine::get()->releaseCompiledShader();


}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,0,0.3,0.5,1);


	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);

	m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{

	/*m_chime.release();
	m_soundEngine.Release();*/

	Window::onDestroy();
	m_vb->Release();
	m_vs->Release();
	m_ps->Release();
	m_swap_chain->release();
	GraphicsEngine::get()->Release();

}
