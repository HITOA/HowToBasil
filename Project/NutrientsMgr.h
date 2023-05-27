#ifndef NUTRIENTSMGR_HEADER
#define NUTRIENTSMGR_HEADER

#include "ProjectConfig.h"

#define PUMP_NUTRIENTS 0

namespace NutrientsMgr
{
  static int   currentNutrients        = 69420;
  static int   nutrientsStatus         = STATUS_IDLE;
  static int   targetNutrients         = 200;
  static int   nutrientsTolerance      = 20;
  static int   nutrientsStep           = 500;
  static int   nutrientsAdjustCooldown = 2000;
  static int   nutrientsTestCooldown   = 60 * 1000;

  static unsigned long actionEndTime = END_OF_TIME;
  static unsigned long nextTestTime  = END_OF_TIME;

  void RunStepNutrientsUp();
  void SetTarget(float target);
  void SetTolerance(float tolerance);
  void SetStep(int step);
  void SetAdjustCooldown(int cooldown);
  void SetTestCooldown(int cooldown);
  void TestNutrients();
  void Update();
}

#endif