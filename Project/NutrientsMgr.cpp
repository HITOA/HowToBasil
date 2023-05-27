#include "NutrientsMgr.h"

#include <arduino.h>
#include <stdio.h>

#include "Serial.h"

void NutrientsMgr::RunStepNutrientsUp()
{
  SERIAL_PRINTLN("Activating Nutrients Pump");
  actionEndTime = millis() + nutrientsStep;
  digitalWrite(PUMP_NUTRIENTS, HIGH);
}

void NutrientsMgr::SetTarget(float target)
{
  SERIAL_PRINTF("Setting target Nutrients PPM to %f \n", target);
  targetNutrients = target;
}

void NutrientsMgr::SetTolerance(float tolerance)
{
  SERIAL_PRINTF("Setting Nutrients tolerance PPM to %f \n", tolerance);
  nutrientsTolerance = tolerance;
}

void NutrientsMgr::SetStep(int step)
{
  SERIAL_PRINTF("Setting Nutrients step duration to %d ms \n", step);
  nutrientsStep = step;
}

void NutrientsMgr::SetAdjustCooldown(int cooldown)
{
  SERIAL_PRINTF("Setting Nutrients adjust cooldown duration to %d ms \n", cooldown);
  nutrientsAdjustCooldown = cooldown;
}

void NutrientsMgr::SetTestCooldown(int cooldown)
{
  SERIAL_PRINTF("Setting Nutrients test cooldown duration to %d ms \n", cooldown);
  nutrientsTestCooldown = cooldown;
}

void NutrientsMgr::TestNutrients()
{
  SERIAL_PRINTLN("Testing Nutrients");
  nextTestTime = millis() + nutrientsTestCooldown;
}

void NutrientsMgr::Update()
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