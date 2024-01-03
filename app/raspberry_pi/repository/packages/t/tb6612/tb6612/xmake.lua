add_requires("pigpio")

target("tb6612")
    set_kind("headeronly")
    add_headerfiles("include/(TB6612.hpp)")
    add_includedirs("include")
    add_packages("pigpio")
