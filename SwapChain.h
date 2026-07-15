#pragma once
#include <d3d11.h>

class DeviceContext;

class SwapChain
{
public:
	SwapChain();
	bool init(HWND hwnd, UINT width, UINT height);

	bool present(bool vsync);



	bool release();
	~SwapChain();
private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_rtv;
	ID3D11Texture2D* m_depthBuffer = nullptr;
	ID3D11DepthStencilView* m_dsv = nullptr;
	ID3D11DepthStencilState* m_depthStencilState = nullptr;
private:
	friend class DeviceContext; 
};

