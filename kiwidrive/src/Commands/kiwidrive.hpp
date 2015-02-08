#ifndef EXAMPLE_COMMAND_H
#define EXAMPLE_COMMAND_H

#include "CommandBase.hpp"
#include <PIDController.h>
#include <utility>

std::pair<float, float> normalize_joystick_axis(float x, float y);
std::tuple<float, float, float> get_wheel_magnitude(float, float, float, float, float, float);

class KiwiDrive : public CommandBase {
 private:
  float pid_output_;
  PIDController* pid_;
  float last_rot_;
  int last_angle_;
  int last_angle_cooldown_;
  bool waiting_to_reenable_;
 public:
  KiwiDrive();
  void Initialize();
  void Execute();
  void raw_drive(float, float, float);
  bool IsFinished();
  void End();
  void Interrupted();
};

#endif
