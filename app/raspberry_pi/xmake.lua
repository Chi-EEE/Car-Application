add_rules("mode.debug", "mode.release")

set_languages("cxx17")

add_repositories("local-repo repository")

-- Messaging System
add_requires("ixwebsocket", {configs = {use_tls = true, ssl = "mbedtls"}})
add_requires("nod")

-- Terminal UI
add_requires("ftxui")

add_requires("nlohmann_json")
add_requires("spdlog")
add_requires("fmt")

-- Get System Info
add_requires("sys_info")

if is_plat("linux", "macosx") then
    -- For the SunFounder Car
    add_requires("pca9685")
    add_requires("tb6612")
end

-- For Functional Programming?
add_requires("tl_expected")

add_requires("rplidar")

target("raspberry_pi")
    set_kind("binary")
    set_license("LGPL-2.1")
            
    add_packages("nlohmann_json")
    add_packages("spdlog")
    add_packages("fmt")

    add_packages("tl_expected")

    -- Get System Info
    add_packages("sys_info")

    -- Messaging System
    add_packages("ixwebsocket")
    add_packages("nod")

    -- UI
    add_packages("ftxui")

    -- For the SunFounder Car
    add_packages("rplidar")
    add_packages("pca9685")
    add_packages("tb6612")

    add_headerfiles("include/**.h")

    add_headerfiles("src/**.h")
    add_files("src/**.cpp", "src/**.cxx")
    
    add_includedirs("include")

    if is_plat("windows") then
        add_defines("_WIN32")
    end

    set_configdir("$(buildir)/$(plat)/$(arch)/$(mode)")
    add_configfiles("settings/config.jsonc", {onlycopy = true, prefixdir = "settings"})
target_end()
    
-- From xmake sample code:
if is_plat("linux") then
    for _, file in ipairs(os.files("tests/pca9685/test_*.cpp")) do
        local name = path.basename(file)
        target(name)
            set_kind("binary")
            set_default(false)
            set_license("LGPL-2.1")
            
            add_packages("pca9685")

            add_files("tests/pca9685/" .. name .. ".cpp")
        target_end()
    end
    for _, file in ipairs(os.files("tests/tb6612/test_*.cpp")) do
        local name = path.basename(file)
        target(name)
            set_kind("binary")
            set_default(false)
            set_license("LGPL-2.1")
            
            add_packages("pca9685")
            add_packages("tb6612")

            add_files("tests/tb6612/" .. name .. ".cpp")
        target_end()
    end
end