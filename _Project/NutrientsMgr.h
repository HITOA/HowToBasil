#include "config.h"

namespace NutrientsMgr
{
  #define PUMP_NUTRIENTS 0
  int   currentNutrients        = 69420;
  int   nutrientsStatus         = STATUS_IDLE;
  int   targetNutrients         = 200;
  int   nutrientsTolerance      = 20;
  int   nutrientsStep           = 500;
  int   nutrientsAdjustCooldown = 2000;
  int   nutrientsTestCooldown   = 60 * 1000;

  unsigned long actionEndTime;
  unsigned long nextTestTime;

  void RunStepNutrientsUp()
  {
    SERIAL_PRINTLN("Activating Nutrients Pump");
    actionEndTime = millis() + nutrientsStep;
    digitalWrite(PUMP_NUTRIENTS, HIGH);
  }

  void SetTarget(float target)
  {
    SERIAL_PRINTF("Setting target Nutrients PPM to %f \n", target);
    targetNutrients = target;
  }

  void SetTolerance(float tolerance)
  {
    SERIAL_PRINTF("Setting Nutrients tolerance PPM to %f \n", tolerance);
    nutrientsTolerance = tolerance;
  }

  void SetStep(int step)
  {
    SERIAL_PRINTF("Setting Nutrients step duration to %d ms \n", step);
    nutrientsStep = step;
  }

  void SetAdjustCooldown(int cooldown)
  {
    SERIAL_PRINTF("Setting Nutrients adjust cooldown duration to %d ms \n", cooldown);
    nutrientsAdjustCooldown = cooldown;
  }

  void SetTestCooldown(int cooldown)
  {
    SERIAL_PRINTF("Setting Nutrients test cooldown duration to %d ms \n", cooldown);
    nutrientsTestCooldown = cooldown;
  }

  void TestNutrients()
  {
    SERIAL_PRINTLN("Testing Nutrients");
    nextTestTime = millis() + nutrientsTestCooldown;
  }

  void Update()
  {
    unsigned long timeElapsed = millis();
    if(timeElapsed > actionEndTime)
    {
      SERIAL_PRINTLN("Stop pumping Nutrients");
      digitalWrite(PUMP_NUTRIENTS, LOW);
    }

    if(timeElapsed > nextTestTime)
    {
      TestNutrients();
    }
  }
}