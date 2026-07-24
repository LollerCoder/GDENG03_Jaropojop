#include "SwapChain.h"
#include "RenderSystem.h"
#include <exception>


SwapChain::SwapChain(HWND hwnd, UINT width, UINT height,RenderSystem* system) : m_system(system)
{
    ID3D11Device* device = m_system->m_d3d_device;

    DXGI_SWAP_CHAIN_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.BufferCount = 1;
    desc.BufferDesc.Width = width;
    desc.BufferDesc.Height = height;
    desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.BufferDesc.RefreshRate.Numerator = 60;
    desc.BufferDesc.RefreshRate.Denominator = 1;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.OutputWindow = hwnd;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Windowed = true;



    HRESULT hr = m_system->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);

    if (FAILED(hr)) {
        throw std::exception("SwapChain not created successfully");
    }

    ID3D11Texture2D* buffer = NULL;
    hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

    if (FAILED(hr)) {
        throw std::exception("D3D11Texture2D not created succesfully");
    }


    hr = device->CreateRenderTargetView(buffer, NULL, &m_rtv);
    buffer->Release();


    if (FAILED(hr)) {
        throw std::exception("CRTV(RenderTargetView) not created successfully");
    }

    D3D11_TEXTURE2D_DESC depthDesc = {};
    depthDesc.Width = width;
    depthDesc.Height = height;
    depthDesc.MipLevels = 1;
    depthDesc.ArraySize = 1;
    depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthDesc.SampleDesc.Count = 1;
    depthDesc.SampleDesc.Quality = 0;
    depthDesc.Usage = D3D11_USAGE_DEFAULT;
    depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

    hr = device->CreateTexture2D(
        &depthDesc,
        nullptr,
        &m_depthBuffer
    );

    if (FAILED(hr))
        throw std::exception("");
    hr = device->CreateDepthStencilView(
        m_depthBuffer,
        nullptr,
        &m_dsv
    );

    if (FAILED(hr))
        throw std::exception("StencilDepthView not created successfully");

    D3D11_DEPTH_STENCIL_DESC dsDesc = {};

    dsDesc.DepthEnable = TRUE;
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

    dsDesc.StencilEnable = FALSE;

    hr = device->CreateDepthStencilState(
        &dsDesc,
        &m_depthStencilState
    );

    if (FAILED(hr))
        throw std::exception("DepthStencilState not created successfully");

    
}


bool SwapChain::present(bool vsync)
{
    m_swap_chain->Present(vsync, NULL);
    return false;
}



SwapChain::~SwapChain()
{
    m_swap_chain->Release();
    if (m_depthStencilState)
        m_depthStencilState->Release();

    if (m_dsv)
        m_dsv->Release();

    if (m_depthBuffer)
        m_depthBuffer->Release();

    if (m_rtv)
        m_rtv->Release();

    if (m_swap_chain)
        m_swap_chain->Release();
}
