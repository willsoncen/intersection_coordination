#pragma once

#include <vector>
#include <memory>
#include "scheduler/vehicle.hpp"

namespace scheduler {

class Scheduler {
private:
    std::vector<std::shared_ptr<Vehicle>> vehicles_;

public:
    Scheduler() = default;
    ~Scheduler() = default;

    void add_vehicle(std::shared_ptr<Vehicle> vehicle);

    void tick(double time_delta);

    const std::vector<std::shared_ptr<Vehicle>>& get_vehicles() const {
        return vehicles_;
    }
    };

}




