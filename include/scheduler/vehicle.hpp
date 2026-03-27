#pragma once
#include <string>
#include <optional>

namespace scheduler {
// 抽象出的物理状态结构体
struct VehicleState {
    double speed;
    double distance_to_conflict;
    // 未来可扩展：
    // double acceleration = 0.0;
    // double x = 0.0;
    // double y = 0.0;
    // double heading = 0.0;
};

class Vehicle {
protected:
    std::string id_;
    VehicleState state_; // 组合状态结构体

public:
    // 构造函数可以直接接收状态
    Vehicle(std::string id, VehicleState state)
        : id_(std::move(id)), state_(std::move(state)) {}

    // 为了使用方便，提供直接传入速度和距离的构造函数
    Vehicle(std::string id, double speed, double distance)
        : id_(std::move(id)), state_{speed, distance} {}

    // 允许外部直接获取整个状态的只读引用 / 拷贝
    [[nodiscard]] const VehicleState& get_state() const { return state_; }
    
    // 提供快捷方法获取速度和距离，方便上层（如 scheduler 和 main）直接调用
    [[nodiscard]] double get_speed() const { return state_.speed; }
    [[nodiscard]] double get_distance() const { return state_.distance_to_conflict; }
    
    [[nodiscard]] const std::string& get_id() const { return id_; }

    virtual ~Vehicle() = default;

    [[nodiscard]] virtual double determine_acceleration(double default_accel) const {
        return default_accel;
    }

    [[nodiscard]] virtual std::optional<std::string> get_emergency_type() const {
        return std::nullopt;
    }

    virtual void update_state(double time_delta, double acceleration);
};

// 进阶优化 3：使用 final 关键字封印继承树，帮助编译器进行性能优化
class EmergencyVehicle final : public Vehicle {
private:
    std::string emergency_type_;

public:
    // 同样使用传值 + 分别对基类及自身成员使用 std::move
    EmergencyVehicle(std::string id, double speed, double distance, std::string type)
        : Vehicle(std::move(id), VehicleState{speed, distance}), emergency_type_(std::move(type)) {}

    [[nodiscard]] double determine_acceleration(double /*default_accel*/) const override {
        return 1.5; // 给紧急车辆设定的加速度
    }

    [[nodiscard]] std::optional<std::string> get_emergency_type() const override {
        return emergency_type_;
    }
};

}

