#include "UIManager.h"
#include "AppWindow.h"
#include "GraphicsEngine.h"

//IMGUI
#include "IMGUI/imgui.h"
#include "IMGUI/backends/imgui_impl_win32.h"
#include "IMGUI/backends/imgui_impl_dx11.h"


#include "Libs/DirectXTex/include/DirectXTex.h"

ID3D11ShaderResourceView* g_logo = nullptr;

UIManager* UIManager::sharedInstance = nullptr;

UIManager* UIManager::getInstance()
{
    return sharedInstance;
}

void UIManager::initialize(HWND windowHandle)
{
    if (sharedInstance == nullptr)
    {
        sharedInstance = new UIManager(windowHandle);
    }
}

void UIManager::destroy()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    delete sharedInstance;
    sharedInstance = nullptr;
}

void UIManager::drawAllUI()
{
    if (g_logo == nullptr)
    {
        DirectX::ScratchImage image;

        HRESULT hr = DirectX::LoadFromWICFile(
            L"Imgs/dlsulogo.jpg",          
            DirectX::WIC_FLAGS_NONE,
            nullptr,
            image);

        if (SUCCEEDED(hr))
        {
            DirectX::CreateShaderResourceView(
                GraphicsEngine::get()->getRenderSystem()->getDevice(),
                image.GetImages(),
                image.GetImageCount(),
                image.GetMetadata(),
                &g_logo);
        }
    }
    // Setup Dear ImGui context
    

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("SpawnObjects"))
        {

            if (ImGui::MenuItem("Color Picker"))
            {
                colorPicker = true;
            }


            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("About"))
        {
            
            if (ImGui::MenuItem("Credits"))
            {
                showCredits = true;
            }
            

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    if (showCredits)
    {
        ImGui::Begin("Credits", &showCredits);
        if (g_logo)
            ImGui::Image((ImTextureID)g_logo, ImVec2(128, 128));
        ImGui::Separator();
        ImGui::Text("The LMAO Engine");
        ImGui::Separator();
        ImGui::Text("Created by Jairo Rio M. Jaropojop");
        ImGui::Text("Based off of PardCode's Game Engine Tutorial Series");

        ImGui::End();
    }

    if (colorPicker)
    {
        ImGui::Begin("Color Picker", &colorPicker);

        ImGui::ColorPicker3("Color", clearColor);
        

        ImGui::End();
    }


    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

}

UIManager::UIManager(HWND windowHandle)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();




    // Setup Platform/Renderer bindings
    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(windowHandle);
    ImGui_ImplDX11_Init(GraphicsEngine::get()->getRenderSystem()->getDevice(), GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->getContext());
}

UIManager::~UIManager()
{

}
