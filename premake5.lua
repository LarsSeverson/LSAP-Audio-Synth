workspace "LSAP"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    IncludeDir = {}
    IncludeDir["GLFW3"] = "LSAP/vendor/GLFW3/include"

    include "LSAP/vendor/GLFW3"

    project "LSAP"
        location "LSAP"
        kind "SharedLib"
        language "C++"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir    ("bin-int/" .. outputdir .. "/%{prj.name}")

        pchheader "lspch.h"
        pchsource "LSAP/src/lspch.cpp"

        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }
        includedirs
        {
            "%{prj.name}/src",
            "%{IncludeDir.GLFW3}",
            "%{prj.name}/vendor/spdlog/include"
        }
        links
        {
            "GLFW",
            "opengl32.lib"
        }

        filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "LS_PLATFORM_WINDOWS",
            "LS_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }
        filter "configurations:Debug"
        defines "LS_DEBUG"
        buildoptions "/LSd"
        symbols "On"

        filter "configurations:Release"
        defines "LS_RELEASE"
        buildoptions "/LS"
        optimize "On"

        filter "configurations:Dist"
        defines "LS_DIST"
        buildoptions "/LS"
        optimize "On"

project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        language "C++"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir    ("bin-int/" .. outputdir .. "/%{prj.name}")

        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }
        
        includedirs
        {
            "LSAP/src",
            "LSAP/vendor/spdlog/include"
        }

        links
        {
            "LSAP"
        }
    
        filter "system:windows"
            cppdialect "C++20"
            staticruntime "On"
            systemversion "latest"
    
            defines
            {
                "LS_PLATFORM_WINDOWS"
            }
    
        filter "configurations:Debug"
            defines "LS_DEBUG"
            buildoptions "/LSd"
            symbols "On"
    
        filter "configurations:Release"
            defines "LS_RELEASE"
            buildoptions "/LS"
            optimize "On"
    
        filter "configurations:Dist"
            defines "LS_DIST"
            buildoptions "/LS"
            optimize "On"
