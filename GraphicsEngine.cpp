#include "GraphicsEngine.h"
#include "RenderSystem.h"

#include <d3dcompiler.h>

GraphicsEngine* GraphicsEngine::sharedInstance = nullptr;

GraphicsEngine::GraphicsEngine()
{
}



void GraphicsEngine::initialize()
{
    if (sharedInstance == nullptr)
    {
        sharedInstance = new GraphicsEngine();
        sharedInstance->init();
    }
}

void GraphicsEngine::destroy()
{
    if (sharedInstance != NULL) {
        sharedInstance->Release();
    }
}

bool GraphicsEngine::init()
{
    m_render_system = new RenderSystem();
    m_render_system->init();
    return true;
}

bool GraphicsEngine::Release()
{

    m_render_system->Release();
    delete m_render_system;
    delete this;
  
    
    return true;
}

GraphicsEngine::~GraphicsEngine()
{
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
    return m_render_system;
}

GraphicsEngine* GraphicsEngine::get()
{

    return sharedInstance;
}


 
