#include <windows.h>

#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include "Application.h"
#include "ImGui/imgui_impl_win32.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
	{
		return true;
	}

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

HWND WinInit(HINSTANCE hInstance)
{
	WCHAR windowClassName[] = L"WindowClass";
	WCHAR windowTitle[] = L"Ball Collison Simulator";
	WNDCLASSW windowClass = { 0, WndProc, 0, 0, 0, 0, 0, 0, 0, windowClassName };

	RegisterClassW(&windowClass);
	HWND windowHandle = CreateWindowExW(
		0,
		windowClassName,
		windowTitle,
		WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1024,
		1024,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	return windowHandle;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	HWND windowHandle = WinInit(hInstance);

	Application application;
	application.Init(windowHandle);
	application.Run();
	application.Clear();

	return 0;
}
