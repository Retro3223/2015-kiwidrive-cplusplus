#ifndef RETROBOTICS_DRIVE_SUBSYSTEM_H
#define RETROBOTICS_DRIVE_SUBSYSTEM_H

#include <PIDOutput.h>
#include <Commands/Subsystem.h>
#include <tuple>
#include <Talon.h>

class Drive : public Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  Talon* wheel_1_;
  Talon* wheel_2_;
  Talon* wheel_3_;

 public:
  Drive();
  void InitDefaultCommand();
  void set_1(float value);
  void set_2(float value);
  void set_3(float value);
  void set(std::tuple<float, float, float> values);
};

#endif
