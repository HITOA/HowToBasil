#ifndef NUTRIENTSMGR_HEADER
#define NUTRIENTSMGR_HEADER

#include "ProjectConfig.h"

#define PUMP_NUTRIENTS 0

namespace NutrientsMgr
{
  int   GetCurrentNutrients();
  int   GetStatus();
  int   GetTarget();
  void  SetTarget(int target);
  int   GetTolerance();
  void  SetTolerance(int tolerance);
  int   GetStep();
  void  SetStep(int step);
  int   GetAdjustCooldown();
  void  SetAdjustCooldown(int cooldown);
  int   GetTestCooldown();
  void  SetTestCooldown(int cooldown);

  void  RunStepNutrientsUp();
  void  StopPumps();
  void  TestNutrients();
  void  Update();
}

#endif