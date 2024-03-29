#include "SazPCH.h"
#include "Application.h"

#include "Saz/Core/GameTime.h"

#include <GLFW/glfw3.h>

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
		//Renderer::Init();
	}

	void Application::PostInit()
	{

		m_Window->PostInit();
	}

	void Application::Register()
	{
	}

	void Application::Destroy()
	{
		m_Window->Destroy();
	}

	void Application::Update(const Saz::GameTime& gameTime)
	{
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
}