
-----------------------------------------------------
-- Saz
-----------------------------------------------------
project "Saz"
	kind		"StaticLib"
	dependson { "Core", "Imgui", "GLFW", "GLAD", "glm", "stb_image" }
	pchheader "SazPCH.h"
	pchsource "Source/Saz/SazPCH.cpp"
	staticruntime "on"

	defines 
	{
		"GLFW_INCLUDE_NONE",
		"_CRT_SECURE_NO_WARNINGS",
	}

	vpaths 
	{ 
		{ ["Source/*"] = {  
			"Source/Saz/**.h", 
			"Source/Saz/**.cpp", 
			"Source/Saz/**.inl" } },
	}

	flags
	{
		"MultiProcessorCompile"
	}

	includedirs {
		"%{wks.location}/Core/Source",
		"%{wks.location}/Saz/Source",
		"%{wks.location}/Saz/Source/Saz",
		"%{wks.location}/3rdParty/",
		"%{wks.location}/3rdParty/spdlog/include",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.ImGui}/imgui",
		"%{IncludeDir.entt}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.Box2D}",
		"%{IncludeDir.Mono}",
	}

	links {
		"Core",
		"ImGui",
		"GLFW",
		"GLAD",
		"Box2D",
		"ImGuizmo",
		"yaml-cpp",
		"opengl32.lib",
	}	

	filter "system:windows"
		systemversion "latest"
		links
		{
			"%{Library.Mono}",
			"%{Library.WinSock}",
			"%{Library.WinMM}",
			"%{Library.WinVersion}",
			"%{Library.BCrypt}",
		}