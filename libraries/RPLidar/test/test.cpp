#include <RPLidar.h>
#include <memory>
#include <spdlog/spdlog.h>
#include <pybind11/embed.h>

int run_native() {
    using namespace rplidar;
    spdlog::set_level(spdlog::level::debug);

    // auto lidar_result = RPLidar::create("/dev/ttyUSB0");
    auto lidar_result = RPLidar::create("COM3");
    if (!lidar_result.has_value())
    {
        return 0;
    }
    auto& lidar = std::move(lidar_result.value());

    auto info_result = lidar->get_info();
    if (!info_result.has_value())
    {
        std::cout << info_result.error();
        return 0;
    }
    auto& info = info_result.value();
    std::cout << fmt::format("model: {}, firmware: ({}, {}), hardware: {}, serialnumber: {}\n", info.model, info.firmware.first, info.firmware.second, info.hardware, info.serialNumber);

    auto health_result = lidar->get_health();
    if (!health_result.has_value())
    {
        std::cout << health_result.error();
        return 0;
    }
    auto& health = health_result.value();
    std::cout << fmt::format("({}, {})\n", health.status, health.errorCode);

    // std::function<std::vector<Measure>()> scanGenerator = lidar->iter_scans();
    // for (int i = 0; i < 10; i++)
    // {
    //     std::vector<Measure> scan = scanGenerator();
    //     std::cout << "Got " << scan.size() << " Measures!\n";
    //     for (const Measure &measure : scan)
    //     {
    //         // Access individual measurements in the scan
    //         bool newScan = measure.newScan;
    //         int quality = measure.quality;
    //         float angle = measure.angle;
    //         float distance = measure.distance;
    //     }
    // }

    lidar->stop();
    lidar->stop_motor();
    lidar->disconnect();
    return 0;
}

void run_python() {
    namespace py = pybind11;
    py::scoped_interpreter guard{};

    auto rplidar = py::module_::import("rplidar");
    auto RPLidar = rplidar.attr("RPLidar");
    auto lidar = RPLidar.call("COM3");

    auto info = lidar.attr("get_info")();
    py::print(info);

    auto health = lidar.attr("get_health")();
    py::print(health);

    lidar.attr("stop")();
    lidar.attr("stop_motor")();
    lidar.attr("disconnect")();
}

int main()
{
    run_native();
    //run_python();
    return 1;
}