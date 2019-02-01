workspace "FSGame"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project "FSEngine"
	location "FSEngine"
	kind "SharedLib"
	language "C++"
	
	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin/" .. outputdir .. "/%{prj.name}/int")

	pchheader "pch.h"
	pchsource "FSEngine/src/pch.cpp"
	
    pic "On"
    
	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h",
	}
	
	includedirs
	{
		"./",
		"%{prj.name}/src/",
		"deps/include",
		"/usr/local/lib64"
	}
	
	libdirs 
	{
		"deps/lib"
	}

	links
	{
        "GLEW",
		"SDL2",
		"pugixml"
	}
	
	filter "system:windows"
		staticruntime "On"
		systemversion "latest"
		links "opengl32"
        characterset("MBCS")
		defines "FSENGINE_EXPORTS"
	filter "system:linux"
		links "GL"
	filter "configurations:Debug"
		defines "FSE_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "FSE_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines
		{
			"FSE_RELEASE",
			"FSE_DIST"
		}
		
		optimize "On"
