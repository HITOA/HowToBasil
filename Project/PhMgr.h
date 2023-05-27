#ifndef PHMGR_HEADER
#define PHMGR_HEADER

#include "ProjectConfig.h"

#define PUMP_PH_DOWN 0
#define PUMP_PH_UP 0

namespace PhMgr
{
  float GetCurrentPh();
  int   GetStatus();
  float GetTarget();
  void  SetTarget(float target);
  float GetTolerance();
  void  SetTolerance(float tolerance);
  int   GetStep();
  void  SetStep(int step);
  int   GetAdjustCooldown();
  void  SetAdjustCooldown(int cooldown);
  int   GetTestCooldown();
  void  SetTestCooldown(int cooldown);

  void RunStepPhDown();
  void RunStepPhUp();
  void StopPumps();
  void TestPh();
  void Update();
}

#endif