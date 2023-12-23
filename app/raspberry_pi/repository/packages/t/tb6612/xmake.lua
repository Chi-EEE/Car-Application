package("tb6612")
    add_deps("cppgpiod")
    set_sourcedir(path.join(os.scriptdir(), "tb6612"))
    on_install(function (package)
        local configs = {}
        import("package.tools.xmake").install(package, configs)
    end)
package_end()