#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"

#include "Quads.h"

#include <vector>



class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;
private: 
	SwapChain* m_swap_chain;
	Quads* work;
private:
	std::vector<Quads*> quadList = {};
private:
	friend class Quads;
	ConstantBuffer* m_cb;
	unsigned long m_old_time = 0;
	float m_delta_time = 0;
	float m_angle = 0;

};

