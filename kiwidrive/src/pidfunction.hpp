#ifndef SRC_PIDFUNCTION_HPP_
#define SRC_PIDFUNCTION_HPP_

#include <PIDSource.h>
#include <PIDOutput.h>
#include <functional>

class PIDFunction : public PIDSource, public PIDOutput {
 private:
  std::function<double ()> producer_;
  std::function<void (float)> consumer_;
 public:
  PIDFunction(std::function<double ()> producer);
  PIDFunction(std::function<void (float)> consumer);
  PIDFunction(std::function<double ()> producer,
              std::function<void (float)> consumer);
  double PIDGet();
  void PIDWrite(float output);
};

#endif /* SRC_PIDFUNCTION_HPP_ */
