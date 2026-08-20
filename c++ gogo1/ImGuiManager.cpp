#include "ImGuiManager.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

ImGuiManager::~ImGuiManager()
{
	Clear();
}

void ImGuiManager::Init(HWND windowHandle, ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	if (IsInitialized)
	{
		return;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX11_Init(device, deviceContext);

	IsInitialized = true;
}

void ImGuiManager::InitFrame()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Setting");
	ImGui::Text("Ball Count & Ball Gravity");
}

void ImGuiManager::ClearFrame()
{
	ImGui::End();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::Clear()
{
	if (!IsInitialized)
	{
		return;
	}

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	IsInitialized = false;
}
