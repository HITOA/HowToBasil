#include "PhMgr.h"
#include "Serial.h"
#include <arduino.h>
#include <stdio.h>

namespace PhMgr
{
  float currentPh        = 69.420;
  int   phStatus         = STATUS_IDLE;
  float targetPh         = 7.0;
  float phTolerance      = 0.5;
  int   phStep           = 500;
  int   phAdjustCooldown = 2000;
  int   phTestCooldown   = 60 * 1000;

  unsigned long actionEndTime = END_OF_TIME;
  unsigned long nextTestTime  = END_OF_TIME;

  float GetCurrentPh()
  {
    return currentPh;
  }

  int GetStatus()
  {
    return phStatus;
  }

  float GetTarget()
  {
    return targetPh;
  }

  void SetTarget(float target)
  {
    SERIAL_PRINTF("Setting target PH to %f \n", target);
    targetPh = target;
  }

  float GetTolerance()
  {
    return phTolerance;
  }

  void SetTolerance(float tolerance)
  {
    SERIAL_PRINTF("Setting tolerance PH to %f \n", tolerance);
    phTolerance = tolerance;
  }

  int GetStep()
  {
    return phStep;
  }

  void SetStep(int step)
  {
    SERIAL_PRINTF("Setting PH step duration to %d ms \n", step);
    phStep = step;
  }

  int GetAdjustCooldown()
  {
    return phAdjustCooldown;
  }

  void SetAdjustCooldown(int cooldown)
  {
    SERIAL_PRINTF("Setting PH adjust cooldown duration to %d ms \n", cooldown);
    phAdjustCooldown = cooldown;
  }

  int GetTestCooldown()
  {
    return phTestCooldown;
  }

  void SetTestCooldown(int cooldown)
  {
    SERIAL_PRINTF("Setting PH test cooldown duration to %d ms \n", cooldown);
    phTestCooldown = cooldown;
  }

  void RunStepPhDown()
  {
    SERIAL_PRINTLN("Activating PH stabilizer pump (lowering PH)");
    phStatus = STATUS_PUMPING_PH_DOWN;
    actionEndTime = millis() + phStep;
    digitalWrite(PUMP_PH_DOWN, HIGH);
  }

  void RunStepPhUp()
  {
    SERIAL_PRINTLN("Activating PH stabilizer pump (boosting PH)");
    phStatus = STATUS_PUMPING_PH_UP;
    actionEndTime = millis() + phStep;
    digitalWrite(PUMP_PH_UP, HIGH);
  }

  void TestPh()
  {
    SERIAL_PRINTLN("Testing PH");
    nextTestTime = millis() + phTestCooldown;
  }

  void StopPumps()
  {
    actionEndTime = END_OF_TIME;
    SERIAL_PRINTLN("Stop pumping PH stabilizer");
    phStatus = STATUS_IDLE;
    digitalWrite(PUMP_PH_DOWN, LOW);
    digitalWrite(PUMP_PH_UP, LOW);
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
      TestPh();
    }
  }
}