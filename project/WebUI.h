#include "PhMgr.h"
#include "NutrientsMgr.h"

namespace WebUI
{
  char pageBuffer[6500];

  const char* webPageUI = "<script type='text/javascript'> \
    function sendCommand(command) \
    { \
      fetch(command, \
      { \
        method: 'POST',\
        headers: {},\
        body: {},\
      });\
    }\
  </script>\
  <html>\
    <body style=\"background-color:black\">\
      <center>\
        <img src=\"https://www.maximumyield.com/images/uploads/logo-trademark-diagram-map-word-collage-poster-ornament-label-text.jpg?w=800&h=0&mode=Max&quality=80&scale=both&bgcolor=000000\"/>\
        <br/><br/>\
        <table style=\"color:white;\">\
          <tr>\
            <td>PH Level:</td>\
            <td>%f</td>\
            <td/>\
          <tr>\
          <tr>\
            <td>Status:</td>\
            <td>%s</td>\
            <td/>\
          <tr>\
          <tr style=\"height:30;\"/>\
          <tr>\
            <td colspan=\"2\"><b>Settings</b></td>\
            <td/>\
          <tr>\
          <tr>\
            <td>Target PH Level:</td>\
            <td><input type=text id='targetPh' value='%f' /><button onclick='sendCommand(\"target-ph?v0=\"+document.getElementById(\"targetPh\").value);'>Set</button></td>\
            <td>*This is the target PH level, the system will try to reach and maintain that level automatically</td>\
          <tr>\
          <tr>\
            <td>PH Level Tolerance:+/-</td>\
            <td><input type=text id='phTolerance' value='%f' /><button onclick='sendCommand(\"tolerance-ph?v0=\"+document.getElementById(\"phTolerance\").value);'>Set</button></td>\
            <td>*Pumps will start adjusting PH if the delta with the target level is greater than the tolerance</td>\
          <tr>\
          <tr>\
            <td>PH Adjustment step (ms):</td>\
            <td><input type=text id='phStep' value='%d'/><button onclick='sendCommand(\"step-ph?v0=\"+document.getElementById(\"phStep\").value);'>Set</button></td>\
            <td>*Pumps will activate for this amount of ms when an adjustment is needed.</td>\
          <tr>\
          <tr>\
            <td>PH Adjustment cooldown (ms):</td>\
            <td><input type=text id='phAdjustCooldown' value='%d'/><button onclick='sendCommand(\"adjust-cooldown-ph?v0=\"+document.getElementById(\"phAdjustCooldown\").value);'>Set</button></td>\
            <td>*Pumps will wait for this amount of ms between Adjustment steps.</td>\
          <tr>\
          <tr>\
            <td>PH Test Cooldown (ms):</td>\
            <td><input type=text id='phTestCooldown' value='%d'/><button onclick='sendCommand(\"test-cooldown-ph?v0=\"+document.getElementById(\"phTestCooldown\").value);'>Set</button></td>\
            <td>*Sensor will wait this amount of ms between PH readings.</td>\
          <tr>\
          <tr style=\"height:30;\"/>\
          <tr>\
            <td>Test PH pumps:</td>\
            <td>\
              <button onclick='sendCommand(\"lower-ph\");'>PH -</button>&nbsp;&nbsp;&nbsp;\
              <button onclick='sendCommand(\"raise-ph\");'>PH +</button>\
            </td>\
            <td>*Manually start pumps for a step duration.</td>\
          <tr>\
          <tr style=\"height:70;\"/>\
          <tr>\
            <td>Nutrients Level:</td>\
            <td>%d ppm</td>\
            <td/>\
          <tr>\
          <tr>\
            <td>Status:</td>\
            <td>%s</td>\
            <td/>\
          <tr>\
          <tr style=\"height:30;\"/>\
          <tr>\
            <td colspan=\"2\"><b>Settings</b></td>\
            <td/>\
          <tr>\
          <tr>\
            <td>Target Nutrients Level (ppm):</td>\
            <td><input type=text id='targetNutrients' value='%d' /><button onclick='sendCommand(\"target-nutrients?v0=\"+document.getElementById(\"targetNutrients\").value);'>Set</button></td>\
            <td>*This is the target Nutrients level, the system will try to reach and maintain that level automatically</td>\
          <tr>\
          <tr>\
            <td>Nutrients Level Tolerance (ppm):+/-</td>\
            <td><input type=text id='nutrientsTolerance' value='%d' /><button onclick='sendCommand(\"tolerance-nutrients?v0=\"+document.getElementById(\"nutrientsTolerance\").value);'>Set</button></td>\
            <td>*Pump will start adding Nutrients if the delta with the target level is greater than the tolerance</td>\
          <tr>\
          <tr>\
            <td>Nutrients Adjustment step (ms):</td>\
            <td><input type=text id='nutrientsStep' value='%d' /><button onclick='sendCommand(\"step-nutrients?v0=\"+document.getElementById(\"nutrientsStep\").value);'>Set</button></td>\
            <td>*Pump will activate for this amount of ms when an adjustment is needed.</td>\
          <tr>\
          <tr>\
            <td>Nutrients Adjustment cooldown (ms):</td>\
            <td><input type=text id='nutrientsAdjustCooldown' value='%d' /><button onclick='sendCommand(\"adjust-cooldown-nutrients?v0=\"+document.getElementById(\"nutrientsAdjustCooldown\").value);'>Set</button></td>\
            <td>*Pump will wait for this amount of ms between Adjustment steps.</td>\
          <tr>\
          <tr>\
            <td>Nutrients Test Cooldown:</td>\
            <td><input type=text id='nutrientsTestCooldown' value='%d' /><button onclick='sendCommand(\"test-cooldown-nutrients?v0=\"+document.getElementById(\"nutrientsTestCooldown\").value);'>Set</button></td>\
            <td>*Sensor will wait this amount of ms between Nutrients readings.</td>\
          <tr>\
          <tr style=\"height:30;\"/>\
          <tr>\
            <td>Test Nutrients pump:</td>\
            <td><button onclick='sendCommand(\"nutrients-raise\");'>Test</button></td>\
            <td>*Manually start pump for a step duration.</td>\
          <tr>\
        </table>\
      </center>\
    </body>\
  </html>\
  ";

  static const char* GetPageUI()
  {
    sprintf(pageBuffer, webPageUI, 
    PhMgr::currentPh,
    PhMgr::phStatus?"Adjusting":"Idle",
    PhMgr::targetPh,
    PhMgr::phTolerance,
    PhMgr::phStep,
    PhMgr::phAdjustCooldown,
    PhMgr::phTestCooldown,
    NutrientsMgr::currentNutrients,
    NutrientsMgr::nutrientsStatus?"Adjusting":"Idle",
    NutrientsMgr::targetNutrients,
    NutrientsMgr::nutrientsTolerance,
    NutrientsMgr::nutrientsStep,
    NutrientsMgr::nutrientsAdjustCooldown,
    NutrientsMgr::nutrientsTestCooldown
    );
    return pageBuffer;
  }
};
