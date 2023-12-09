
package("python-pyserial")
  add_deps("python")

  on_fetch(function (package)
    os.runv("python", {"-m", "pip", "show", "pyserial"})
  end)

  on_install(function (package)
      os.runv("python", {"-m", "pip", "install", "pyserial"})
  end)
package_end()

add_rules("mode.debug", "mode.release")

add_requires("serial", "spdlog")
add_requires("tl_expected")

add_requires("pybind11", "python", {configs = {headeronly = true}})
add_requires("python-pyserial")

target("RPLidar")
    set_kind("static")
    add_files("src/*.cpp")
    add_headerfiles("include/(**.h)")
    add_headerfiles("include/(**.hpp)")
    add_includedirs("include")
    add_packages("spdlog")
    add_packages("tl_expected")
    add_packages("pybind11", "python")
    add_packages("python-pyserial")

target("test")
    set_kind("binary")
    add_files("test/*.cpp")
    add_includedirs("include")
    add_packages("serial", "spdlog")
    add_packages("tl_expected")
    add_packages("pybind11", "python")
    add_packages("python-pyserial")
    add_deps("RPLidar")

