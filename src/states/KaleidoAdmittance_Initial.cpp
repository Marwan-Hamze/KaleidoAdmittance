#include "KaleidoAdmittance_Initial.h"

#include "../KaleidoAdmittance.h"

void KaleidoAdmittance_Initial::configure(const mc_rtc::Configuration & config)
{
}

void KaleidoAdmittance_Initial::start(mc_control::fsm::Controller & ctl_)
{
    ctl_.gui()->addElement({"Controller"}, mc_rtc::gui::Button("Move Right Hand", [this]() { start_ = true; }));
}

bool KaleidoAdmittance_Initial::run(mc_control::fsm::Controller & ctl_)
{
 if(start_)
  {
    output("OK");
    return true;
  }
  return false;
}

void KaleidoAdmittance_Initial::teardown(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KaleidoAdmittance &>(ctl_);
  ctl_.gui()->removeElement({"Controller"},"Move Right Hand");
}

EXPORT_SINGLE_STATE("KaleidoAdmittance_Initial", KaleidoAdmittance_Initial)
