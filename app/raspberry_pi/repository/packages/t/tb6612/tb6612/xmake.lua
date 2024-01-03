add_requires("pigpio")

target("tb6612")
    set_kind("static")
    add_files("src/*.cpp")
    add_headerfiles("include/(TB6612.h)")
    add_includedirs("include")
    add_packages("pigpio")
