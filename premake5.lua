workspace "MainWorkspace"
    configurations { "Debug", "Release" }
    location "build"

project "PhysicsEngine"
    location "build/PhysicsEngine"
    kind "ConsoleApp"
    language "C++"
    files { "**.h", "**.cpp" }

    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"
