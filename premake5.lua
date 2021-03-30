include "./vendor/premake/solution_items.lua"

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}-%{cfg.system}"

includedir                = {}
includedir["GLFW"]        = "%{wks.location}/FakeEngine/vendor/GLFW/include"
includedir["FreeTypeGL"]  = "%{wks.location}/FakeEngine/vendor/FreeTypeGL"
includedir["Glad"]        = "%{wks.location}/FakeEngine/vendor/Glad/include"
includedir["stb_image"]   = "%{wks.location}/FakeEngine/vendor/stb_image"
includedir["Box2D"]       = "%{wks.location}/FakeEngine/vendor/Box2D/include"
includedir["entt"]        = "%{wks.location}/FakeEngine/vendor/entt/include"
includedir["mono"]        = "%{wks.location}/FakeEngine/vendor/mono/include"
includedir["ImGui"]       = "%{wks.location}/FakeEngine/vendor/ImGui"
includedir["yamp_cpp"]    = "%{wks.location}/FakeEngine/vendor/yaml-cpp/include"
includedir["glm"]         = "%{wks.location}/FakeEngine/vendor/glm"
includedir["shaderc"]     = "%{wks.location}/FakeEngine/vendor/shaderc/include"
includedir["SPIRV_Cross"] = "%{wks.location}/FakeEngine/vendor/SPIRV-Cross"
includedir["Vulkan"]      = "%{wks.location}/FakeEngine/vendor/Vulkan/1.2.148.1/Include"
includedir["freetype"]    = "%{wks.location}/FakeEngine/vendor/freetype"
includedir["PhysX"]       = "%{wks.location}/FakeEngine/vendor/PhysX"
includedir["asio"]        = "%{wks.location}/FakeEngine/vendor/asio/include"
includedir["assimp"]      = "%{wks.location}/FakeEngine/vendor/assimp/include"

librarydir                               = {}
librarydir["mono"]                       = "%{wks.location}/FakeEngine/vendor/mono/lib/Debug/mono-2.0-sgen.lib"
librarydir["assimp"]                     = "%{wks.location}/FakeEngine/vendor/assimp/lib/Debug/assimp-vc141-mtd.lib"
librarydir["shaderc"]                    = "%{wks.location}/FakeEngine/vendor/shaderc/lib/Debug/shaderc.lib"
librarydir["shaderc_util"]               = "%{wks.location}/FakeEngine/vendor/shaderc/lib/Debug/shaderc_util.lib"
librarydir["glslang"]                    = "%{wks.location}/FakeEngine/vendor/glslang/lib/Debug/glslangd.lib"
librarydir["glslang_MachineIndependent"] = "%{wks.location}/FakeEngine/vendor/glslang/lib/Debug/MachineIndependentd.lib"
librarydir["glslang_SPIRV"]              = "%{wks.location}/FakeEngine/vendor/glslang/lib/Debug/SPIRVd.lib"
librarydir["glslang_OGLCompiler"]        = "%{wks.location}/FakeEngine/vendor/glslang/lib/Debug/OGLCompilerd.lib"
librarydir["glslang_OSDependent"]        = "%{wks.location}/FakeEngine/vendor/glslang/lib/Debug/OSDependentd.lib"
librarydir["glslang_GenericCodeGen"]     = "%{wks.location}/FakeEngine/vendor/glslang/lib/Debug/GenericCodeGend.lib"
librarydir["SPIRV_Tools"]                = "%{wks.location}/FakeEngine/vendor/SPIRV-Tools/lib/Debug/SPIRV-Tools.lib"
librarydir["SPIRV_Tools_opt"]            = "%{wks.location}/FakeEngine/vendor/SPIRV-Tools/lib/Debug/SPIRV-Tools-opt.lib"
librarydir["Vulkan"]                     = "%{wks.location}/FakeEngine/vendor/Vulkan/1.2.148.1/Lib/vulkan-1.lib"

workspace "FakeEngine"
	architecture "x64"
	
	configurations
		{
		"Debug",
		"Release"
		}
		
	solution_items
		{
		".config"
		}
	
	group "Dependencies"
	include "FakeEngine/vendor/GLFW"
	include "FakeEngine/vendor/Glad"
	include "FakeEngine/vendor/ImGui"
	include "FakeEngine/vendor/Box2D"
	include "FakeEngine/vendor/entt"
	include "FakeEngine/vendor/yaml-cpp"
	include "FakeEngine/vendor/glm"
	group ""
	
	group "tests"
	include "tests/"
	group ""
	
	group "examples"
	include "examples/"
	group ""
	
	include "FakeEngine"
	include "Sandbox"
	include "LevelEditor"
