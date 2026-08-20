#include "Application.h"

#include "Ball.h"
#include "ImGui/imgui.h"
#include "diagram.h"

void Application::Init(HWND windowHandle)
{
	WindowHandle = windowHandle;

	RendererInit();

	ImGui.Init(WindowHandle, Renderer.Device, Renderer.DeviceContext);

	Balls.Init();
	InputBallCount = Balls.GetBallCount();

	FrameRate.Create(30);

	IsInitialized = true;
}

void Application::Run()
{
	if (!IsInitialized)
	{
		return;
	}

	while (!IsExit)
	{
		MSG message;
		while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);

			if (message.message == WM_QUIT)
			{
				IsExit = true;
				break;
			}
		}

		Balls.Update();

		Renderer.Prepare();
		Renderer.PrepareShader();

		Balls.Render(Renderer, SphereBuffer, SphereVertexCount);

		ImGui.InitFrame();

		ImGui::Checkbox("Gravity", &Ball::Gravity);

		if (ImGui::InputInt("Ball Count", &InputBallCount, 1))
		{
			if (InputBallCount < 1)
			{
				InputBallCount = 1;
			}

			Balls.SetBallCount(InputBallCount);
		}

		ImGui.ClearFrame();

		Renderer.SwapBuffer();

		FrameRate.Check();
	}
}

void Application::Clear()
{
	if (!IsInitialized)
	{
		return;
	}

	Balls.Clear();

	RendererClear();

	ImGui.Clear();

	IsInitialized = false;
}

void Application::RendererInit()
{
	Renderer.Create(WindowHandle);
	Renderer.CreateShader();

	SphereVertexCount = sizeof(sphere_vertices) / sizeof(FVertexSimple);
	SphereBuffer = Renderer.CreateVertexBuffer(sphere_vertices, sizeof(sphere_vertices));
	Renderer.CreateConstantBuffer();
}

void Application::RendererClear()
{
	Renderer.ReleaseVertexBuffer(SphereBuffer);
	SphereBuffer = nullptr;

	Renderer.ReleaseConstantBuffer();
	Renderer.ReleaseShader();
	Renderer.Release();
}
