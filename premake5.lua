workspace "Main Workspace"
    filename "MainWorkspace"
    location "build"
    configurations { "Debug", "Release" }

project "Physics Engine"
    filename "PhysicsEngine"
    location "build/PhysicsEngine"
    kind "WindowApp"
    language "C++"
    -- files { "**.h", "**.hpp", "**.cpp" }
    files { 
        "include/Utils.hpp",
        "include/Math.hpp",
        "include/bodies/*.h",
        "include/bodies/*.hpp",
        "include/primitives/*.hpp",
        "src/main.cpp",
        "src/engine/**.cpp",
        "src/engine/**.hpp"
    }
    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"
