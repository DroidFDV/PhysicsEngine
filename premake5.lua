workspace "Main Workspace"
    filename "MainWorkspace"
    location "build"
    configurations { "Debug", "Release" }

project "Physics Engine"
    filename "PhysicsEngine"
    location "build/PhysicsEngine"
    kind "ConsoleApp"
    language "C++"
    -- files { "**.h", "**.hpp", "**.cpp" }
    files {
        "include/Utils.hpp",
        "include/Math.hpp",
        "include/bodies/*.h",
        "include/bodies/*.hpp",
        "include/primitives/*.hpp",
        "src/main.cpp",
        "src/engine/physics/bodies/**.cpp",
        "src/engine/**.hpp"
    }
    libdirs { os.findlib("SFML")}
    links { "sfml-system", "sfml-window", "sfml-graphics" }
    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"
