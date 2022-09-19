#include "SazPCH.h"
#include "Application.h"

#include "Saz/CameraComponent.h"
#include "Saz/Core/EntityWorld.h"
#include "Saz/Core/GameTime.h"
#include "Saz/Systems/CameraSystem.h"
#include "Saz/InputComponent.h"
#include "Saz/Systems/InputSystem.h"
#include "Saz/Systems/RenderSystem.h"
#include "Saz/LevelComponent.h"
#include "Saz/Systems/SceneSystem.h"
#include "Saz/MovementComponent.h"
#include "Saz/RenderComponents.h"
#include "Saz/NameComponent.h"
#include "Saz/Screen.h"
#include "Saz/TransformComponent.h"
#include "Saz/Platform/Windows/WindowsWindow.h"

#include "ImGui/ImGuiLog.h"
#include "imgui/imgui.h"
#include "GLFW/glfw3.h"
#include "Saz/Rendering/Renderer.h"
#include "SceneComponent.h"
#include "Systems/PhysicsSystem.h"
#include "PhysicsComponents.h"

namespace Saz
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const String& name)
	{
		SAZ_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		Saz::Log::Init();

		m_Window = WindowBase::Create(WindowProps(name));
	}

	Application::~Application()
	{
		Destroy();
	}

	void Application::Init()
	{
		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	void Application::PostInit()
	{
		SAZ_PROFILE_FUNCTION();

		m_Window->PostInit();
	}

	void Application::Register()
	{
		SAZ_PROFILE_FUNCTION();
	}

	void Application::Destroy()
	{
		SAZ_PROFILE_FUNCTION();

		m_Window->Destroy();
	}

	void Application::Update(const Saz::GameTime& gameTime)
	{
		SAZ_PROFILE_FUNCTION();

		m_Window->OnUpdate(gameTime);
	}

	void Application::Run()
	{
		Register();
		Init();
		PostInit();

		Saz::GameTime gameTime;

		while (!m_Window->ShouldClose() && m_Running)
		{
			gameTime.m_TotalTime = (float)glfwGetTime();
			gameTime.m_DeltaTime = gameTime.m_TotalTime - m_LastFrameTime;
			gameTime.m_Frame++;
			m_LastFrameTime = gameTime.m_TotalTime;

			Update(gameTime);
		}
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
}