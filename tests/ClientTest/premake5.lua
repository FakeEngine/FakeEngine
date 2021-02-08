project "ClientTest"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	entrypoint "mainCRTStartup"

	defines
		{
		"_CRT_SECURE_NO_WARNINGS"
		}

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
		{
		"src/**.c",
		"src/**.h",
		"src/**.hpp",
		"src/**.cpp"
		}
		
	includedirs
		{
		"src",
		"../../FakeEngine/src",
		"../../FakeEngine/vendor",
		"%{includedir.entt}",
		"%{includedir.asio}"
		}
		
	postbuildcommands
		{
		'{COPY} "assets" "%{cfg.targetdir}/assets"'
		}
		
	links
		{
		"FakeEngine",
		"%{librarydir.assimp}"
		}
		
	filter "system:macosx"
		systemversion "latest"
		defines "PLATFORM_MACOS"
			
		filter "configurations:Debug"
			defines "_DEBUG"
			runtime "Debug"
			symbols "on"

			postbuildcommands 
				{
				'{COPY} "../../FakeEngine/vendor/assimp/lib/Debug/assimp-vc141-mtd.dll" "%{cfg.targetdir}"',
				'{COPY} "../../FakeEngine/vendor/mono/lib/Debug/mono-2.0-sgen.dll" "%{cfg.targetdir}"'
				}
		
		filter "configurations:Release"
			defines "_RELEASE"
			runtime "Release"
			optimize "on"

			postbuildcommands 
				{
				'{COPY} "../../FakeEngine/vendor/assimp/lib/Release/assimp-vc141-mt.dll" "%{cfg.targetdir}"',
				'{COPY} "../../FakeEngine/vendor/mono/lib/Release/mono-2.0-sgen.dll" "%{cfg.targetdir}"'
				}
			
	filter "system:linux"
		systemversion "latest"
		defines "PLATFORM_LINUX"
			
		filter "configurations:Debug"
			defines "_DEBUG"
			runtime "Debug"
			symbols "on"

			postbuildcommands 
				{
				'{COPY} "../../FakeEngine/vendor/assimp/lib/Debug/assimp-vc141-mtd.dll" "%{cfg.targetdir}"',
				'{COPY} "../../FakeEngine/vendor/mono/lib/Debug/mono-2.0-sgen.dll" "%{cfg.targetdir}"'
				}
		
		filter "configurations:Release"
			defines "_RELEASE"
			runtime "Release"
			optimize "on"
			
			postbuildcommands 
				{
				'{COPY} "../../FakeEngine/vendor/assimp/lib/Release/assimp-vc141-mt.dll" "%{cfg.targetdir}"',
				'{COPY} "../../FakeEngine/vendor/mono/lib/Release/mono-2.0-sgen.dll" "%{cfg.targetdir}"'
				}
			
	filter "system:windows"
		systemversion "latest"
		defines "PLATFORM_WINDOWS"
			
		filter "configurations:Debug"
			defines "_DEBUG"
			runtime "Debug"
			symbols "on"

			postbuildcommands 
				{
				'{COPY} "../../FakeEngine/vendor/assimp/lib/Debug/assimp-vc141-mtd.dll" "%{cfg.targetdir}"',
				'{COPY} "../../FakeEngine/vendor/mono/lib/Debug/mono-2.0-sgen.dll" "%{cfg.targetdir}"'
				}
		
		filter "configurations:Release"
			defines "_RELEASE"
			runtime "Release"
			optimize "on"
			
			postbuildcommands 
				{
				'{COPY} "../../FakeEngine/vendor/assimp/lib/Release/assimp-vc141-mt.dll" "%{cfg.targetdir}"',
				'{COPY} "../../FakeEngine/vendor/mono/lib/Release/mono-2.0-sgen.dll" "%{cfg.targetdir}"'
				}