#include <iostream>
#include <iomanip> // 引入 I/O 格式化库，面试加分项
#include <thread>
#include <chrono>
#include <memory>
// 引入路口协调系统的头文件
#include "scheduler/vehicle.hpp"
#include "scheduler/scheduler.hpp"

using namespace scheduler;

int main() {
    std::cout << "=== 交叉口协同调度引擎 v2.0 启动 ===" << std::endl;

    // 1. 初始化路口调度器
    Scheduler intersection_manager;

    // 2. 实例化多辆网联车 (使用现代 C++ std::make_shared 分配到“堆”上)
    // 假设这些车从不同方向开来
    auto car1 = std::make_shared<Vehicle>("CAV-001", 15.0, 100.0);
    auto car2 = std::make_shared<Vehicle>("CAV-002", 20.0, 150.0);
    
    // 第三阶段应用多态：添加一辆急救车，速度快，距离远，不受全局指令限制
    std::shared_ptr<Vehicle> emergency_car = std::make_shared<EmergencyVehicle>("AMB-911", 10.0, 80.0, "Ambulance");

    // 把它们注册到调度系统中
    intersection_manager.add_vehicle(car1);
    intersection_manager.add_vehicle(car2);
    intersection_manager.add_vehicle(emergency_car);

    // 3. 设置仿真参数
    double time_delta = 1.0;       // 每次仿真步长为 1.0 秒
    double current_time = 0.0;     // 初始时间

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Time(s) | Vehicle ID | Speed(m/s) | Distance(m)\n";
    std::cout << "------------------------------------------------\n";

    // 4. 仿真主循环：假设运行 15 步 (也就是 15 秒)
    for (int step = 0; step < 15; ++step) {
        // 先打印所有车辆在这一秒初的状态
        for (const auto& vehicle : intersection_manager.get_vehicles()) {
            std::string type_str = "Normal";
            auto e_type = vehicle->get_emergency_type();
            if (e_type.has_value()) {
                type_str = "[" + e_type.value() + "]";
            }

            std::cout << std::setw(7) << current_time << " | "
                      << std::setw(10) << vehicle->get_id() << " | "
                      << std::setw(11) << type_str << " | "
                      << std::setw(10) << vehicle->get_speed() << " | "
                      << std::setw(11) << vehicle->get_distance() << "\n";
        }
        std::cout << "------------------------------------------------\n";

        // 让调度器统一下发指令
        intersection_manager.tick(time_delta);

        current_time += time_delta;
        
        // 睡眠 500 毫秒方便动态观察终端更新
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "[INFO] 仿真运行完毕。\n";

    return 0;
}