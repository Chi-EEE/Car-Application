package("rplidar")
    add_deps("serial", "spdlog", "tl_expected")
    set_sourcedir(path.join(os.scriptdir(), "rplidar"))
    on_install(function (package)
        local configs = {}
        import("package.tools.xmake").install(package, configs)
    end)
package_end()