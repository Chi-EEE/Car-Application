add_rules("mode.debug", "mode.release")

add_requires("serial", "spdlog")

target("RPLidar")
    set_kind("static")
    add_files("src/*.cpp")
    add_headerfiles("include/(**.h)")
    add_headerfiles("include/(**.hpp)")
    add_includedirs("include")
    add_packages("serial", "spdlog")

target("test")
    set_kind("binary")
    add_files("test/*.cpp")
    add_includedirs("include")
    add_packages("serial", "spdlog")
    add_deps("RPLidar")
