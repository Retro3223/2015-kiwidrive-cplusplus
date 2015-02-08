#ifndef OI_H
#define OI_H

#include <Gyro.h>
#include <Joystick.h>
#include <Talon.h>
#include <tuple>

class OI {
 private:

 public:
  OI();
  Gyro* gyro_;
  Joystick* joy_;
  std::tuple<Talon*, Talon*, Talon*> motors_;
  //Talon* motor0_;
  //Talon* motor1_;
  //Talon* motor2_;
};

#endif
