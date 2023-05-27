#ifndef BASILWEBSERVER_HEADER
#define BASILWEBSERVER_HEADER

namespace BasilWebServer
{
  void HandleRoot();
  void HandleNotFound();
  void LowerPh();
  void RaisePh();
  void SetTargetPh();
  void SetTolerancePh();
  void SetStepPh();
  void SetAdjustCooldownPh();
  void SetTestCooldownPh();
  void RaiseNutrients();
  void SetTargetNutrients();
  void SetToleranceNutrients();
  void SetStepNutrients();
  void SetAdjustCooldownNutrients();
  void SetTestCooldownNutrients();
  void Setup();
  void Update();
}

#endif