#include "Subsystems/drive.hpp"
#include <Commands/Subsystem.h>
#include "CommandBase.hpp"
#include <tuple>

Drive::Drive()
    : Subsystem{"Drive"},
      wheel_1_(new Talon{0}),
      wheel_2_(new Talon{1}),
      wheel_3_(new Talon{2}) {
}

void Drive::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  //SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Drive::set_1(float value) {
  wheel_1_->Set(value);
}
void Drive::set_2(float value) {
  wheel_2_->Set(value);
}
void Drive::set_3(float value) {
  wheel_3_->Set(value);
}
void Drive::set(std::tuple<float, float, float> values) {
  set_1(std::get<0>(values));
  set_2(std::get<1>(values));
  set_3(std::get<2>(values));
}
