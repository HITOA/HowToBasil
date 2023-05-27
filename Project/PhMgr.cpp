#include "PhMgr.h"

#include <arduino.h>
#include <stdio.h>

#include "Serial.h"

void PhMgr::RunStepPhDown()
{
  SERIAL_PRINTLN("Activating PH stabilizer pump (lowering PH)");
  actionEndTime = millis() + phStep;
  digitalWrite(PUMP_PH_DOWN, HIGH);
}

void PhMgr::RunStepPhUp()
{
  SERIAL_PRINTLN("Activating PH stabilizer pump (boosting PH)");
  actionEndTime = millis() + phStep;
  digitalWrite(PUMP_PH_UP, HIGH);
}

void PhMgr::SetTarget(float target)
{
  SERIAL_PRINTF("Setting target PH to %f \n", target);
  targetPh = target;
}

void PhMgr::SetTolerance(float tolerance)
{
  SERIAL_PRINTF("Setting tolerance PH to %f \n", tolerance);
  phTolerance = tolerance;
}

void PhMgr::SetStep(int step)
{
  SERIAL_PRINTF("Setting PH step duration to %d ms \n", step);
  phStep = step;
}

void PhMgr::SetAdjustCooldown(int cooldown)
{
  SERIAL_PRINTF("Setting PH adjust cooldown duration to %d ms \n", cooldown);
  phAdjustCooldown = cooldown;
}

void PhMgr::SetTestCooldown(int cooldown)
{
  SERIAL_PRINTF("Setting PH test cooldown duration to %d ms \n", cooldown);
  phTestCooldown = cooldown;
}

void PhMgr::TestPh()
{
  SERIAL_PRINTLN("Testing PH");
  nextTestTime = millis() + phTestCooldown;
}

void PhMgr::Update()
{
  unsigned long timeElapsed = millis();
  if(timeElapsed > actionEndTime)
  {
    SERIAL_PRINTLN("Stop pumping PH stabilizer");
    digitalWrite(PUMP_PH_DOWN, LOW);
    digitalWrite(PUMP_PH_UP, LOW);
  }

  if(timeElapsed > nextTestTime)
  {
      TestPh();
  }
}