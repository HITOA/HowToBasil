#include "data.h"

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

  void runStepPhDown()
  {
    Serial.println("Activating PH stabilizer pump (lowering PH)");
    actionEndTime = millis() + phStep;
    digitalWrite(PUMP_PH_DOWN, HIGH);
  }

  void runStepPhUp()
  {
    Serial.println("Activating PH stabilizer pump (boosting PH)");
    actionEndTime = millis() + phStep;
    digitalWrite(PUMP_PH_UP, HIGH);
  }

  void setTarget(float target)
  {
    Serial.printf("Setting target PH to %f \n", target);
    targetPh = target;
  }

  void setTolerance(float tolerance)
  {
    Serial.printf("Setting tolerance PH to %f \n", tolerance);
    phTolerance = tolerance;
  }

  void setStep(int step)
  {
    Serial.printf("Setting PH step duration to %d ms \n", step);
    phStep = step;
  }

  void setAdjustCooldown(int cooldown)
  {
    Serial.printf("Setting PH adjust cooldown duration to %d ms \n", cooldown);
    phAdjustCooldown = cooldown;
  }

  void setTestCooldown(int cooldown)
  {
    Serial.printf("Setting PH test cooldown duration to %d ms \n", cooldown);
    phTestCooldown = cooldown;
  }

  void testPh()
  {
    Serial.println("Testing PH");
    nextTestTime = millis() + phTestCooldown;
  }

  void update()
  {
    unsigned long timeElapsed = millis();
    if(timeElapsed > actionEndTime)
    {
      Serial.println("Stop pumping PH stabilizer");
      digitalWrite(PUMP_PH_DOWN, LOW);
      digitalWrite(PUMP_PH_UP, LOW);
    }

    if(timeElapsed > nextTestTime)
    {
        testPh();
    }
  }
}