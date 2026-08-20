#pragma once

#include <windows.h>

#include "BallManager.h"
#include "ImGuiManager.h"
#include "URenderer.h"

class Application
{
public:
	void Init(HWND windowHandle);
	void Run();
	void Clear();

private:
	void RendererInit();
	void RendererClear();

	struct FrameLimiter
	{
		double TargetFrameTime = 0.0;
		LARGE_INTEGER Frequency = {};
		LARGE_INTEGER StartTime = {};

		void Create(int targetFPS)
		{
			TargetFrameTime = 1000.0 / targetFPS;
			QueryPerformanceFrequency(&Frequency);
			QueryPerformanceCounter(&StartTime);
		}

		void Check()
		{
			LARGE_INTEGER endTime;
			double elapsedTime;

			do
			{
				Sleep(0);
				QueryPerformanceCounter(&endTime);
				elapsedTime = (endTime.QuadPart - StartTime.QuadPart)
					* 1000.0 / Frequency.QuadPart;
			} while (elapsedTime < TargetFrameTime);

			StartTime = endTime;
		}
	};

	HWND WindowHandle = nullptr;
	bool IsExit = false;
	bool IsInitialized = false;

	URenderer Renderer;
	ImGuiManager ImGui;
	BallManager Balls;
	FrameLimiter FrameRate;

	ID3D11Buffer* SphereBuffer = nullptr;
	UINT SphereVertexCount = 0;
	int InputBallCount = 1;
};
