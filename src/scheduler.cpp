#include "scheduler/scheduler.hpp"

namespace scheduler {

void Scheduler::add_vehicle(std::shared_ptr<Vehicle> vehicle) {
    if (vehicle) {
        vehicles_.push_back(vehicle);
    }
}

void Scheduler::tick(double time_delta) {
    // 假设阶段二的调度系统比较基础：发现所有车辆立刻统一给出 -2.0 的平缓减速指令
    double default_acceleration = -2.0;

    // 现代 C++11/17 语法特性：基于范围的 for 循环 (Range-based for loop)
    // auto& 会自动推导类型，并获取容器元素的引用，这里不发生拷贝
    for (auto& vehicle : vehicles_) {
        // 多态应用：调用 determine_acceleration 获取对应车辆决定使用的加速度
        double actual_accel = vehicle->determine_acceleration(default_acceleration);

        // 因为 vehicle 是智能指针，要使用 -> 运算符调用类的方法
        if (vehicle->get_distance() > 0.0 && vehicle->get_speed() > 0.0) {
            vehicle->update_state(time_delta, actual_accel);
        }
    }
}

} // namespace scheduler
