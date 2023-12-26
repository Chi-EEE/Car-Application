add_requires("pigpio")

target("tb6612")
    set_kind("$(kind)")
    add_headerfiles("include/(TB6612.h)")
    add_includedirs("include")
    add_files("src/TB6612.cpp")
    add_packages("pigpio")
