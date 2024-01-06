package("sys_info")
    set_homepage("https://github.com/Chi-EEE/sys_info")
    set_description("c++ crossplatform cpu and memory usage info by current process")

    add_urls("https://github.com/Chi-EEE/sys_info.git")
    add_versions("2024.01.06", "1e8dd0275ecf9a94473a0933f746cb5c873afd96")

    on_install(function (package)
        local configs = {}
        import("package.tools.xmake").install(package, configs)
    end)

    on_test(function (package)
        assert(package:check_cxxsnippets({test = [[
            #include "sys_info/ProcessInfo.h"
            void test () {
                sys_info::ProcessInfo::GetInstance().GetCpuUsage();
            }
        ]]}, {configs = {languages = "c++11"}}))
    end)
