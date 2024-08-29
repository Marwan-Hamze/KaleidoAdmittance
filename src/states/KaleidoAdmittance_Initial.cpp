#include "KaleidoAdmittance_Initial.h"

#include "../KaleidoAdmittance.h"

void KaleidoAdmittance_Initial::configure(const mc_rtc::Configuration & config)
{
}

void KaleidoAdmittance_Initial::start(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KaleidoAdmittance &>(ctl_);
}

bool KaleidoAdmittance_Initial::run(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KaleidoAdmittance &>(ctl_);
  output("OK");
  return true;
}

void KaleidoAdmittance_Initial::teardown(mc_control::fsm::Controller & ctl_)
{
  auto & ctl = static_cast<KaleidoAdmittance &>(ctl_);
}

EXPORT_SINGLE_STATE("KaleidoAdmittance_Initial", KaleidoAdmittance_Initial)
