#include "NutrientsMgr.h"
#include "Serial.h"
#include <arduino.h>
#include <stdio.h>

namespace NutrientsMgr
{
  int   currentNutrients        = 69420;
  int   nutrientsStatus         = STATUS_IDLE;
  int   targetNutrients         = 200;
  int   nutrientsTolerance      = 20;
  int   nutrientsStep           = 500;
  int   nutrientsAdjustCooldown = 2000;
  int   nutrientsTestCooldown   = 60 * 1000;

  unsigned long actionEndTime = END_OF_TIME;
  unsigned long nextTestTime  = END_OF_TIME;



  int GetCurrentNutrients()
  {
    return currentNutrients;
  }

  int GetStatus()
  {
    return nutrientsStatus;
  }

  int GetTarget()
  {
    return targetNutrients;
  }

  void SetTarget(int target)
  {
    SERIAL_PRINTF("Setting target Nutrients PPM to %d \n", target);
    targetNutrients = target;
  }

  int GetTolerance()
  {
    return nutrientsTolerance;
  }

  void SetTolerance(int tolerance)
  {
    SERIAL_PRINTF("Setting Nutrients tolerance PPM to %d \n", tolerance);
    nutrientsTolerance = tolerance;
  }

  int GetStep()
  {
    return nutrientsStep;
  }

  void SetStep(int step)
  {
    SERIAL_PRINTF("Setting Nutrients step duration to %d ms \n", step);
    nutrientsStep = step;
  }

  int GetAdjustCooldown()
  {
    return nutrientsAdjustCooldown;
  }

  void SetAdjustCooldown(int cooldown)
  {
    SERIAL_PRINTF("Setting Nutrients adjust cooldown duration to %d ms \n", cooldown);
    nutrientsAdjustCooldown = cooldown;
  }

  int GetTestCooldown()
  {
    return nutrientsTestCooldown;
  }

  void SetTestCooldown(int cooldown)
  {
    SERIAL_PRINTF("Setting Nutrients test cooldown duration to %d ms \n", cooldown);
    nutrientsTestCooldown = cooldown;
  }

  void RunStepNutrientsUp()
  {
    SERIAL_PRINTLN("Activating Nutrients Pump");
    nutrientsStatus = STATUS_PUMPING_NUTRIENTS;
    actionEndTime = millis() + nutrientsStep;
    digitalWrite(PUMP_NUTRIENTS, HIGH);
  }

  void TestNutrients()
  {
    SERIAL_PRINTLN("Testing Nutrients");
    nextTestTime = millis() + nutrientsTestCooldown;
  }

  void StopPumps()
  {
    actionEndTime = END_OF_TIME;
    SERIAL_PRINTLN("Stop pumping Nutrients");
    nutrientsStatus = STATUS_IDLE;
    digitalWrite(PUMP_NUTRIENTS, LOW);
  }

  void Update()
  {
    unsigned long timeElapsed = millis();
    if(timeElapsed > actionEndTime)
    {
      StopPumps();
    }

    if(timeElapsed > nextTestTime)
    {
      TestNutrients();
    }
  }
}
