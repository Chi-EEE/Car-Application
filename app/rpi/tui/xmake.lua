add_rules("mode.debug", "mode.release")

add_requires("ixwebsocket", {configs = {use_tls = true, ssl = "mbedtls"}})
add_requires("cxxopts", "fmt", "rapidjson", "robin-map", "spdlog", "tl_expected", "nod")
add_requires("serial")
add_requires("effolkronium-random", "pugixml")
add_requires("ftxui")

includes("../common/xmake.lua")

target("rpi_tui")
    set_kind("binary")
    set_languages("cxx17")
    
    add_packages("ixwebsocket")
    add_packages("cxxopts", "fmt", "rapidjson", "robin-map", "spdlog", "tl_expected", "nod")
    add_packages("serial")
    add_packages("effolkronium-random", "pugixml")
    add_packages("ftxui")

    add_headerfiles("src/**.h")
    add_files("src/**.cpp", "src/**.cxx")

    add_deps("rpi_common", {public = true})