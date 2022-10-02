add_rules("mode.debug", "mode.release")

add_requires("libsdl", "libsdl_image")
add_packages("libsdl", "libsdl_image")

set_allowedarchs("windows|x64")
set_warnings("allextra")
set_languages("c++20")

target("Game")
    set_kind("binary")
    add_headerfiles("include/Game/*.h", "include/Game/*.hpp")
    add_includedirs("include/Game")
    add_files("src/Game/*.cpp")

    set_rundir("bin/Game") -- Le dossier courant lors de l'exécution des binaires (depuis VS) - c'est depuis ce dossier que les chemins commencent
    set_targetdir("bin/Game/$(plat)_$(arch)_$(mode)") -- Le dossier de sortie des binaires, les $(X) sont remplacés par les valeurs existantes (plat = windows, arch = x64 et mode = debug)
    
    add_deps("Engine")

target("Engine")
    set_kind("shared")
    add_files("src/Engine/*.cpp")
    add_headerfiles("include/Engine/*.h", "include/Engine/*.hpp")
    add_includedirs("include/Engine", {public = true})
    add_defines("ENGINE_EXPORT")

    set_rundir("bin/Engine") -- Le dossier courant lors de l'exécution des binaires (depuis VS) - c'est depuis ce dossier que les chemins commencent
    set_targetdir("bin/Engine/$(plat)_$(arch)_$(mode)") -- Le dossier de sortie des binaires, les $(X) sont remplacés par les valeurs existantes (plat = windows, arch = x64 et mode = debug)
--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro defination
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--
