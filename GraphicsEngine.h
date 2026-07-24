#pragma once
#include "d3d11.h"
#include "Prerequisites.h"
#include "RenderSystem.h"

class GraphicsEngine
{
public:
	GraphicsEngine();
	void initialize();
	void destroy();
	bool init();
	bool Release();
	
	~GraphicsEngine();
	RenderSystem* getRenderSystem();
	

private:
	GraphicsEngine(GraphicsEngine* const&) {};
	GraphicsEngine& operator=(GraphicsEngine* const&) {};
	static GraphicsEngine* sharedInstance;
	RenderSystem* m_render_system = nullptr;
	

public:
	static GraphicsEngine* get();

	
};

