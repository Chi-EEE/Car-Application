#include <RPLidar.h>
#include <memory>
#include <spdlog/spdlog.h>

int main()
{
    spdlog::set_level(spdlog::level::debug);

    auto lidar = std::make_unique<RPLidar>("COM3");
    //auto lidar = std::make_unique<RPLidar>("/dev/ttyUSB0");

    auto info = lidar->get_info();
    std::cout << fmt::format("model: {}, firmware: ({}, {}), hardware: {}, serialnumber: {}\n", info.model, info.firmware.first, info.firmware.second, info.hardware, info.serialNumber);

    auto health = lidar->get_health();
    std::cout << fmt::format("({}, {})\n", health.status, health.errorCode);

    std::function<std::vector<Measure>()> scanGenerator = lidar->iter_scans();
    for (int i = 0; i < 10; i++)
    {
        std::vector<Measure> scan = scanGenerator();
        std::cout << "Got " << scan.size() << " Measures!\n";
        for (const Measure &measure : scan)
        {
            // Access individual measurements in the scan
            bool newScan = measure.newScan;
            int quality = measure.quality;
            float angle = measure.angle;
            float distance = measure.distance;
        }
    }

    lidar->stop();
    lidar->stop_motor();
    lidar->disconnect();
    return 0;
}