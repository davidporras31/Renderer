workspace "Renderer"
    architecture "x86_64"
    startproject "core"
    configurations { "Test", "Debug", "Release", "Dist" }
project "core"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++23"
    staticruntime "off"

    runpathdirs { "$$ORIGIN" }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")
    targetname "renderer"

    --pchheader "hzpch.h"
    --pchsource "src/hzpch.cpp"

    files
    {
        "src/**.cpp",
        "test/**.cpp",
        "lib/shader-precompiler/ShaderPrecompiler.cpp",
        "lib/glad/build/src/gl.c",
    }

    defines
    {
        "GLFW_INCLUDE_NONE"
    }

    includedirs
    {
        "include",
        "test",
        "lib/glad/build/include",
        "lib/glfw/include",
        "lib/glm",
        "lib/stb",
        "lib/ft2/include",
        "lib/assimp/include",
        "lib/assimp/build/include",
    }

    libdirs
    {
        "lib/glfw/build/src",
        "lib/ft2/objs/.libs",
        "lib/assimp/build/bin",
        "lib/resource-manager/bin",
        "lib/glm/build/glm",
    }

    links
    {
        "glfw",
        "freetype",
        "assimp",
        "resourcemanager",
        "glm",
    }
    local so_files = os.matchfiles("lib/**.so")

    local cmds = {}
    for _, file in ipairs(so_files) do
        if path.getname(file) ~= "_speedups.cpython-314-x86_64-linux-gnu.so" then
            table.insert(cmds, "$(SILENT) {COPY} -L " .. file .. " %{cfg.targetdir}; {ECHO} copy " .. path.getname(file))
            end
        end
    table.insert(cmds, "$(SILENT) {COPY} -L test %{cfg.targetdir}/test; {ECHO} copy test")
    table.insert(cmds, "$(SILENT) {COPY} -L shaders %{cfg.targetdir}/shaders; {ECHO} copy shaders")

    postbuildcommands(cmds)

    filter "system:windows"
    systemversion "latest"

    defines
    {
    }

    links
    {
        "Ws2_32",
        "Winmm",
        "Version",
        "Bcrypt",
    }

    filter "configurations:Test"
        defines
        {
            "RE_DEBUG",
            "TESTMODE"
        }
        runtime "Debug"
        symbols "on"

        links
        {
        }

    filter "configurations:Debug"
        defines "RE_DEBUG"
        runtime "Debug"
        symbols "on"

        links
        {
        }

    filter "configurations:Release"
        defines "RE_RELEASE"
        runtime "Release"
        optimize "on"

        links
        {
        }

    filter "configurations:Dist"
        kind "SharedLib"
        defines "RE_DIST"
        runtime "Release"
        optimize "on"

        links
        {
        }
