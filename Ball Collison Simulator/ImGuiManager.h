#pragma once

#include <d3d11.h>
#include <windows.h>

class ImGuiManager
{
public:
	~ImGuiManager();

	void Init(HWND windowHandle, ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void InitFrame();
	void ClearFrame();
	void Clear();

private:
	bool IsInitialized = false;
};
