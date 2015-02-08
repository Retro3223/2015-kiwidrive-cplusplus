#include "CommandBase.hpp"
#include "OI.hpp"
#include <string>
#include "Subsystems/drive.hpp"

// Initialize a single static instance of all of your subsystems to nullptr
OI* CommandBase::oi_ = nullptr;
Drive* CommandBase::drive_ = nullptr;

CommandBase::CommandBase(std::string name)
    : Command{name.c_str()} {
}

CommandBase::CommandBase()
    : Command{} {
}

void CommandBase::init() {
  // Create a single static instance of all of your subsystems.
  oi_ = new OI{};
  drive_ = new Drive{};
}
