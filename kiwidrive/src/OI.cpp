#include "OI.hpp"
#include <Gyro.h>
#include <Joystick.h>

OI::OI()
    : gyro_{new Gyro{1}},
      joy_{new Joystick{0}},
      motors_{new Talon{0}, new Talon{1}, new Talon{2}} {
}
