#include "scheduler/vehicle.hpp"
#include <algorithm> // 为了使用 std::max

namespace scheduler {

// 使用 作用域解析运算符 (::) 来实现类的方法
void Vehicle::update_state(double time_delta, double acceleration) {
    // 1. 先计算距离 (使用更新前的旧速度计算)
    double distance_moved = (state_.speed * time_delta) + (0.5 * acceleration * time_delta * time_delta);
    
    // 距离不能为负数（到达冲突点后停留在 0）
    state_.distance_to_conflict = std::max(0.0, state_.distance_to_conflict - distance_moved);

    // 2. 再更新速度
    state_.speed = std::max(0.0, state_.speed + acceleration * time_delta);
}

} // namespace scheduler