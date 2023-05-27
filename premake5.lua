workspace "Main Workspace"
    filename "MainWorkspace"
    location "build"
    configurations { "Debug", "Release" }

project "Physics Engine"
    filename "PhysicsEngine"
    location "build/PhysicsEngine"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

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

    includedirs {
        "include"
    }

    libdirs { os.findlib("SFML")}
    links { "sfml-system", "sfml-window", "sfml-graphics" }

    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"

-- outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

newaction {
    trigger = "clean",
    description = "Remove all binaries and intermediate binaries, and vs files.",
    execute = function()
        print("Removing binaries")
        os.rmdir("./build")
        print("Removing intermediate binaries")
        os.rmdir("./bin-int")
        print("Removing project files")
        os.rmdir("./.vs")
        os.remove("**.sln")
        os.remove("**.vcxproj")
        os.remove("**.vcxproj.filters")
        os.remove("**.vcxproj.user")
        print("Done")
    end
}
