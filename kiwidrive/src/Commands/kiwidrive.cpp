#include "pidfunction.hpp"
#include "Commands/KiwiDrive.hpp"
#include <PIDController.h>
#include <tuple_utils.hpp>
#include "CommandBase.hpp"
#include <Talon.h>
#include <cmath>
#include <utility>
#include <tuple>
#include <cstdlib>
#include "tuple_utils.hpp"

std::pair<float, float> normalize_joystick_axes(float x, float y) {
  float magnitude = std::hypot(x, y);
  float side = std::max(std::abs(x), std::abs(y));

  if (magnitude == 0.0) {
    return {0, 0};
  }

  return {x * side / magnitude, y * side / magnitude};
}
std::tuple<float, float, float> get_wheel_magnitudes(
    std::pair<float, float> xy) {
  float x = xy.first, y = xy.second;
  return std::tuple<float, float, float>{-1.28 * x, 0.8 * x + -0.75 * y, 0.8 * x
      + 0.75 * y};
}

KiwiDrive::KiwiDrive()
    : CommandBase{"KiwiDrive"},
      pid_output_{0},
      pid_{new PIDController{0.015, 0.0, 0.0, .1, oi_->gyro_, new PIDFunction{
          [&](float output) {pid_output_ = output;}}}},
      last_rot_{0},
      last_angle_{0},
      last_angle_cooldown_{0},
      waiting_to_reenable_{false} {
  Requires(drive_);
}

// Called just before this Command runs the first time
void KiwiDrive::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void KiwiDrive::Execute() {
  float x = oi_->joy_->GetRawAxis(4);
  // if the joystick is moved less than the threshold
  if (std::abs(x) < .2) {
    x = 0;
  }
  float y = oi_->joy_->GetRawAxis(1);
  // if the joystick is moved less than the threshold
  if (std::abs(y) < .2) {
    y = 0;
  }

  float rotation = oi_->joy_->GetRawAxis(3) + -oi_->joy_->GetRawAxis(2);

  raw_drive(x, y, rotation);
}

void KiwiDrive::raw_drive(float x, float y, float rotation) {
  auto xy = normalize_joystick_axes(x, y);
  auto motor_values = get_wheel_magnitudes(xy);

  if (rotation != 0) {
    pid_->Reset();
  }
  if (rotation == 0 && last_rot_ != 0) {
    waiting_to_reenable_ = true;
  } else if (waiting_to_reenable_) {
    if (last_angle_ == oi_->gyro_->PIDGet()) {
      last_angle_cooldown_++;
    } else {
      last_angle_cooldown_ = 0;
    }

    if (last_angle_cooldown_ >= 10) {
      waiting_to_reenable_ = false;
      pid_->SetSetpoint(oi_->gyro_->PIDGet());
      pid_->Enable();
    }
  }

  last_angle_ = oi_->gyro_->PIDGet();
  last_rot_ = rotation;

  auto motors_values = tuple_zip(oi_->motors_, motor_values);

  for_each(motors_values, [&](auto motor_value) {
    auto motor = motor_value.first;
    auto value = motor_value.second;
    value += rotation * .3;
    if(value < 0) {
      value *= .8;  // motor bias
    }

    value += pid_output_;
    motor->Set(value);
  });

}

// Make this return true when this Command no longer needs to run execute()
bool KiwiDrive::IsFinished() {
  return false;
}

// Called once after isFinished returns true
void KiwiDrive::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void KiwiDrive::Interrupted() {

}
