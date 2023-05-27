#ifndef PHMGR_HEADER
#define PHMGR_HEADER

#include "ProjectConfig.h"

#define PUMP_PH_DOWN 0
#define PUMP_PH_UP 0

namespace PhMgr
{
  static float currentPh        = 69.420;
  static int   phStatus         = STATUS_IDLE;
  static float targetPh         = 7.0;
  static float phTolerance      = 0.5;
  static int   phStep           = 500;
  static int   phAdjustCooldown = 2000;
  static int   phTestCooldown   = 60 * 1000;

  static unsigned long actionEndTime;
  static unsigned long nextTestTime;

  void RunStepPhDown();
  void RunStepPhUp();
  void SetTarget(float target);
  void SetTolerance(float tolerance);
  void SetStep(int step);
  void SetAdjustCooldown(int cooldown);
  void SetTestCooldown(int cooldown);
  void TestPh();
  void Update();
}

#endif