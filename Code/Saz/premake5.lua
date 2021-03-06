
-----------------------------------------------------
-- Saz
-----------------------------------------------------

project "Saz"
	kind		"StaticLib"
	dependson { "Core", "Imgui", "GLFW", "Glad" }
	location	"%{wks.location}/Projects/Saz"
	pchheader "SazPCH.h"
	pchsource "Saz/SazPCH.cpp"

	defines 
	{
		"RAYLIB_CPP_NO_MATH" 
	}

	vpaths 
	{ 
		{ ["Source/*"] = {  
			"Saz/**.h", 
			"Saz/**.cpp", 
			"Saz/**.inl" } },
	}

	flags
	{
		"MultiProcessorCompile"
	}

	IncludeDir = {}
	IncludeDir["ImGui"] = "%{wks.location}/3rdParty/imgui"
	IncludeDir["entt"] = "%{wks.location}/3rdParty/entt/include"
	IncludeDir["spdlog"] = "%{wks.location}/3rdParty/spdlog/include"

	includedirs {
		"%{wks.location}/Code/Core/",
		"%{wks.location}/Code/Saz/",
		"%{wks.location}/3rdParty/",
		"%{wks.location}/3rdParty/spdlog/include",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.entt}",
		"%{wks.location}/3rdParty/raylib-cpp",
		"%{wks.location}/3rdParty/raylib-cpp/rlImGui",
		"%{wks.location}/3rdParty/raylib-cpp/include",
		"%{wks.location}/3rdParty/raylib-cpp/vendor/raylib/src/"
	}

	libdirs
	{
		"%{wks.location}/Build/Core/%{cfg.buildcfg}_%{cfg.platform}/",
		"%{wks.location}/Build/ImGui/%{cfg.buildcfg}_%{cfg.platform}/",
	}

	links {
		"Core",
		"ImGui",
		"RayLib",
	}

	filter "system:windows"
		systemversion "latest"

		defines{
			"SAZ_PLATFORM_WINDOWS",
			"SAZ_BUILD_DLL",
		}

	filter "files:%{wks.location}/3rdParty/**.cpp"
		flags { "NoPCH" }

	