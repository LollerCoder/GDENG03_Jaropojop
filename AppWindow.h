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
#include "InputListener.h"
#include "Matrix4x4.h"
#include "Plane.h"


class AppWindow : public Window, public InputListener
{
public:
	AppWindow();

	void update();


	~AppWindow();

	static void init();
	// Inherited via Window
	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;
	void onFocus() override;
	void onKillFocus() override;

	void CreateGraphicsWindow();

	static AppWindow* get();

	static AppWindow* sharedInstance;



private: 

	AppWindow(AppWindow const&) {};
	AppWindow& operator=(AppWindow const&) {};
	SwapChainPtr m_swap_chain;
	Quads* work;
	Cube* cubeWork;
	Plane* plane;
	bool m_activate_cam;
	
	
private:
	std::vector<Quads*> quadList = {};
	std::vector<Cube*> cubeList = {};

private:
	
	ConstantBufferPtr m_cb;
	
	float speed = 1;
	float m_angle = 0;
	float m_delta_pos;
	float m_delta_scale;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;
	float m_scale_cube = 1.0f;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;
	Matrix4x4 m_world_cam;


	// Inherited via InputListener
	void onKeyDown(int key) override;

	void onKeyUp(int key) override;


	// Inherited via InputListener
	void onMouseMove(const Point& mouse_pos) override;

	void onRightMouseDown(const Point& mouse_pos) override;
	void onRightMouseUp(const Point& mouse_pos) override;

	void onLeftMouseDown(const Point& mouse_pos) override;
	void onLeftMouseUp(const Point& mouse_pos) override;

};

