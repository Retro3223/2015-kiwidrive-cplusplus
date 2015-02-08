#include "pidfunction.hpp"
#include <PIDOutput.h>
#include <functional>

PIDFunction::PIDFunction(std::function<double()> producer)
    : PIDOutput{},
      producer_{producer} {
}

PIDFunction::PIDFunction(std::function<void(float)> consumer)
    : PIDOutput{},
      consumer_{consumer} {
}

PIDFunction::PIDFunction(std::function<double ()> producer,
    std::function<void (float)> consumer) : producer_{producer}, consumer_{consumer} {
}

double PIDFunction::PIDGet() {
  return producer_();
}

void PIDFunction::PIDWrite(float output) {
  consumer_(output);
}
