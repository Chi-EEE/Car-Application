add_requires("serial", "spdlog")
add_requires("tl_expected")

add_requires("pybind11", "python", {configs = {headeronly = true}})

-- target("RPLidar")
--     set_kind("static")
--     add_files("src/*.cpp")
--     add_headerfiles("include/(**.h)")
--     add_headerfiles("include/(**.hpp)")
--     add_includedirs("include")
--     add_packages("serial", "spdlog")
--     add_packages("tl_expected")

target("test")
    set_kind("binary")
    add_files("test/*.cpp")
    add_includedirs("include")
    add_packages("serial", "spdlog")
    add_packages("tl_expected")
    -- add_deps("RPLidar")
    add_packages("pybind11", "python")

