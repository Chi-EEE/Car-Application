package("tb6612")
    add_deps("pigpio")
    set_sourcedir(path.join(os.scriptdir(), "tb6612"))
    set_policy("package.install_always", true)
    on_install(function (package)
        local configs = {}
        import("package.tools.xmake").install(package, configs)
    end)
package_end()