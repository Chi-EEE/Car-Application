#ifndef PLUGIN_H
#define PLUGIN_H

#pragma once

#include <string>
#include <memory>

namespace car::system
{
    class CarSystem;
}

namespace car::plugin
{
    class Plugin
    {
    public:
        virtual void initialize(std::shared_ptr<car::system::CarSystem> car_system) = 0;
        virtual void update() = 0;
        virtual void stop() = 0;
        virtual std::string getName() = 0;
    };
}

#endif