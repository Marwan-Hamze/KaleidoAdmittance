#include "MoveRightFoot.h"

#include "../KaleidoAdmittance.h"

void MoveRightFoot::configure(const mc_rtc::Configuration & config)
{
}

void MoveRightFoot::start(mc_control::fsm::Controller & ctl_)
{
    ctl_.gui()->addElement({"Controller"}, mc_rtc::gui::Button("Move Right Foot", [this]() { start_ = true; }));
}

bool MoveRightFoot::run(mc_control::fsm::Controller & ctl_)
{
 if(start_)
  {
    output("OK");
    return true;
  }
  return false;
}

void MoveRightFoot::teardown(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KaleidoAdmittance &>(ctl_);
  ctl_.gui()->removeElement({"Controller"},"Move Right Foot");
}

EXPORT_SINGLE_STATE("MoveRightFoot", MoveRightFoot)
