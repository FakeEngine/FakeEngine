project "FakeEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "FakePch.h"
	pchsource "src/FakePch.cpp"
	
	defines
		{
		"_CRT_SECURE_NO_WARNINGS",
		"FAKE_RENDERER_OPENGL",
		"FAKE_LIBRARY_EXPORT",
		"FAKE_PLATFORM_64BITS",
		"FAKE_ENABLE_PROFILER" -- TODO: move this to debug configuration --
		}
		
	files
		{
		"src/**.c",
		"src/**.h",
		"src/**.hpp",
		"src/**.cpp",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp"
		}
		
	includedirs
		{
		"src",
		"%{includedir.assimp}",
		"%{includedir.GLFW}",
		"%{includedir.Glad}",
		"%{includedir.stb_image}",
		"%{includedir.ImGui}",
		"%{includedir.Box2D}",
		"%{includedir.entt}",
		"%{includedir.mono}",
		"%{includedir.yamp_cpp}",
		"%{includedir.asio}",
		

		"%{includedir.Vulkan}",
		"%{includedir.glm}"
		}
		
	links
		{
		"GLFW",
		"Glad",
		"ImGui",
		"Box2D",
		"yaml-cpp",
		"opengl32.lib",
		
		"%{librarydir.Vulkan}",
		"%{librarydir.mono}",
		"%{librarydir.assimp}"
		}
		
	filter "system:macosx"
		systemversion "latest"
		
		defines
			{
			"FAKE_PLATFORM_MACOS",
			"FAKE_WINAPI_MACOS"
			}
			
		filter "configurations:Debug"
			defines "FAKE_DEBUG"
			runtime "Debug"
			symbols "on"
		
		filter "configurations:Release"
			defines "FAKE_RELEASE"
			runtime "Release"
			optimize "on"
			
	filter "system:linux"
		systemversion "latest"
		
		defines
			{
			"FAKE_PLATFORM_LINUX",
			"GLFW_INCLUDE_NONE",
			"FAKE_WINAPI_GLFW"
			}
			
		filter "configurations:Debug"
			defines "FAKE_DEBUG"
			runtime "Debug"
			symbols "on"
		
		filter "configurations:Release"
			defines "FAKE_RELEASE"
			runtime "Release"
			optimize "on"
			
	filter "system:windows"
		systemversion "latest"
		
		defines
			{
			"FAKE_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE",
			"FAKE_WINAPI_WINDOWS"
			}
			
		filter "configurations:Debug"
			defines "FAKE_DEBUG"
			runtime "Debug"
			symbols "on"
		
		filter "configurations:Release"
			defines "FAKE_RELEASE"
			runtime "Release"
			optimize "on"