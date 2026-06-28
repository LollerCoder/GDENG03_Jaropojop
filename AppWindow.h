#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "Quads.h"
#include "EngineTime.h"
#include <vector>
#include "Cube.h"



class AppWindow : public Window
{
public:
	AppWindow();

	void updateQuadPosition();


	~AppWindow();

	// Inherited via Window
	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;
private: 
	SwapChain* m_swap_chain;
	Quads* work;
	Cube* cubeWork;
private:
	std::vector<Quads*> quadList = {};
	std::vector<Cube*> cubeList = {};
private:
	
	ConstantBuffer* m_cb;
	
	float speed = 1;
	float m_angle = 0;
	float m_delta_pos;
	float m_delta_scale;

};

