workspace "MainWorkspace"
    location "build"
    configurations { "Debug", "Release" }

project "Engine"
    filename ("engine")
    location "build/Core"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    -- files { "**.h", "**.hpp", "**.cpp" }

    files {
        "include/Utils.hpp",
        "include/Math.hpp",
        -- "include/bodies/*.h",
        -- "include/bodies/*.hpp",
        -- "include/primitives/*.hpp",
        -- "src/main.cpp",
        -- "src/engine/physics/bodies/**.cpp",
        -- "src/engine/**.hpp"
        "include/bodies/Verlet.hpp",
        "src/engine/Arbiter.cpp",
        "src/engine/Renderer.hpp",
        "src/main.cpp"
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
