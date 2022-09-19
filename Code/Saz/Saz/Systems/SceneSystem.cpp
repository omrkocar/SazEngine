#include "SazPCH.h"
#include "SceneSystem.h"

#include "Saz/SceneComponent.h"
#include "Saz/SceneSerializer.h"
#include "Saz/Rendering/Renderer.h"
#include "Saz/Core/Application.h"
#include "CameraComponent.h"

namespace ecs
{	
	constexpr char* strLastOpenScene = "LastOpenScene.txt";

	void SceneSystem::Init()
	{
		auto entity = m_World->CreateEntity();
		m_Scene = &m_World->AddComponent<component::LoadedSceneComponent>(entity);

		Saz::SceneSerializer serializer(*m_World);
		const String& scenePath = serializer.DeserializeLastOpenScene(strLastOpenScene);
		m_Scene->Path = scenePath;
		UpdateWindowName(scenePath);

		auto& registry = m_World->m_Registry;
		registry.on_construct<component::SceneStateChangeRequestOneFrameComponent>().connect<&SceneSystem::OnSceneStateChangeRequest>(this);
	}

	void SceneSystem::Destroy()
	{
		Saz::SceneSerializer serializer(*m_World);
		auto& sceneComp = m_World->GetSingleComponent<component::LoadedSceneComponent>();
		if (sceneComp.Path != "")
		{
			serializer.SerializeLastOpenScene(strLastOpenScene, sceneComp.Path);
		}
	}

	void SceneSystem::Update(const Saz::GameTime& gameTime)
	{
		const auto newSceneView = m_World->GetAllEntitiesWith<component::NewSceneRequestOneFrameComponent>();
		for (const auto& newSceneEntity : newSceneView)
		{
			auto& sceneRequestComp = m_World->m_Registry.get<component::NewSceneRequestOneFrameComponent>(newSceneEntity);
			NewScene();
		}

		const auto loadSceneView = m_World->GetAllEntitiesWith<component::LoadSceneRequestOneFrameComponent>();
		for (const auto& loadSceneEntity : loadSceneView)
		{
			auto& sceneRequestComp = m_World->m_Registry.get<component::LoadSceneRequestOneFrameComponent>(loadSceneEntity);
			LoadScene(sceneRequestComp.Path);
		}

		const auto saveSceneView = m_World->GetAllEntitiesWith<component::SaveSceneRequestOneFrameComponent>();
		for (const auto& saveSceneEntity : saveSceneView)
		{
			auto& sceneRequestComp = m_World->m_Registry.get<component::SaveSceneRequestOneFrameComponent>(saveSceneEntity);
			SaveScene(sceneRequestComp.Path);
		}
	}

	void SceneSystem::NewScene()
	{
		m_World->DestroyEntitesWith<component::SceneEntityComponent>();
		m_World->CreateMainCamera();
		UpdateWindowName("");
	}

	void SceneSystem::LoadScene(const String& scenePath)
	{
		const auto sceneEntityView = m_World->GetAllEntitiesWith<component::SceneEntityComponent>();
		for (const auto& sceneEntity : sceneEntityView)
		{
			m_World->DestroyEntity(sceneEntity);
		}

		Saz::SceneSerializer serializer(*m_World);
		serializer.Deserialize(scenePath);
		
		UpdateWindowName(scenePath);
	}

	void SceneSystem::SaveScene(const String& scenePath)
	{
		int num = 0;
		const auto sceneEntityView = m_World->GetAllEntitiesWith<component::EditorCameraComponent>();
		for (const auto& sceneEntity : sceneEntityView)
		{
			num++;
		}

		Saz::SceneSerializer serializer(*m_World);
		serializer.Serialize(scenePath);

		UpdateWindowName(scenePath);
	}

	void SceneSystem::UpdateWindowName(const String& scenePath)
	{
		auto& scene = m_World->GetSingleComponent<component::LoadedSceneComponent>();
		scene.Path = scenePath;
		String name = "Empty Scene";
		if (scenePath.empty() == false)
		{
			name = scenePath.substr(scenePath.find_last_of("/\\") + 1);
			name.erase(name.rfind('.'));
		}
		
		scene.Name = name;
		auto& window = Saz::Application::Get().GetWindow();
		window.SetTitle(String("Saz Editor") + " - " + scene.Name);
	}

	void SceneSystem::OnSceneStateChangeRequest(entt::registry& registry, entt::entity entity)
	{
		auto& sceneStateRequest = m_World->GetComponent<component::SceneStateChangeRequestOneFrameComponent>(entity);

		if (sceneStateRequest.SceneState == SceneState::Play)
		{
			Saz::SceneSerializer serializer(*m_World);
			serializer.Serialize("EditorScene.saz");

			m_Scene->SceneState = SceneState::Play;
		}
		else if (sceneStateRequest.SceneState == SceneState::Editor)
		{
			const auto sceneEntityView = m_World->GetAllEntitiesWith<component::SceneEntityComponent>();
			for (const auto& sceneEntity : sceneEntityView)
			{
				m_World->DestroyEntity(sceneEntity);
			}

			Saz::SceneSerializer serializer(*m_World);
			serializer.Deserialize("EditorScene.saz");
			m_Scene->SceneState = SceneState::Editor;
		}
	}
}
