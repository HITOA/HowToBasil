#include "config.h"

namespace PhMgr
{
  #define PUMP_PH_DOWN 0
  #define PUMP_PH_UP 0
  float currentPh        = 69.420;
  int   phStatus         = STATUS_IDLE;
  float targetPh         = 7.0;
  float phTolerance      = 0.5;
  int   phStep           = 500;
  int   phAdjustCooldown = 2000;
  int   phTestCooldown   = 60 * 1000;

  unsigned long actionEndTime;
  unsigned long nextTestTime;

  void RunStepPhDown()
  {
    SERIAL_PRINTLN("Activating PH stabilizer pump (lowering PH)");
    actionEndTime = millis() + phStep;
    digitalWrite(PUMP_PH_DOWN, HIGH);
  }

  void RunStepPhUp()
  {
    SERIAL_PRINTLN("Activating PH stabilizer pump (boosting PH)");
    actionEndTime = millis() + phStep;
    digitalWrite(PUMP_PH_UP, HIGH);
  }

  void SetTarget(float target)
  {
    SERIAL_PRINTF("Setting target PH to %f \n", target);
    targetPh = target;
  }

  void SetTolerance(float tolerance)
  {
    SERIAL_PRINTF("Setting tolerance PH to %f \n", tolerance);
    phTolerance = tolerance;
  }

  void SetStep(int step)
  {
    SERIAL_PRINTF("Setting PH step duration to %d ms \n", step);
    phStep = step;
  }

  void SetAdjustCooldown(int cooldown)
  {
    SERIAL_PRINTF("Setting PH adjust cooldown duration to %d ms \n", cooldown);
    phAdjustCooldown = cooldown;
  }

  void SetTestCooldown(int cooldown)
  {
    SERIAL_PRINTF("Setting PH test cooldown duration to %d ms \n", cooldown);
    phTestCooldown = cooldown;
  }

  void TestPh()
  {
    SERIAL_PRINTLN("Testing PH");
    nextTestTime = millis() + phTestCooldown;
  }

  void Update()
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
}