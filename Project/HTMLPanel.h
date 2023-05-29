EMBED_FILE(

<div class="panel-container">
    <div class="panel">
        <div class="panel-header">
            <h1>PH Settings</h1>
            <div class="horizontal-box">
                <h2>PH Level: %f</h2>
                <h2>Status: %s</h2>
            </div>
        </div>
        <table>
            <tbody>
                <tr>
                    <td>Target PH</td><td><input value="%f" id="targetPhInput"><button onclick='sendCommand("target-ph?v0="+document.getElementById("targetPhInput").value)'>Set</button></td>
                </tr>
                <tr>
                    <td>PH Level Tolerance +/-</td><td><input value="%f" id="phToleranceInput"><button onclick='sendCommand("tolerance-ph?v0="+document.getElementById("phToleranceInput").value)'>Set</button></td>
                </tr>
                <tr>
                    <td>PH Adjustment Step (ms)</td><td><input value="%d" id="phAdjustmentStepInput"><button onclick='sendCommand("step-ph?v0="+document.getElementById("phAdjustmentStepInput").value)'>Set</button></td>
                </tr>
                <tr>
                    <td>PH Adjustment Cooldown (ms)</td><td><input value="%d" id="phAdjustmentCooldownInput"><button onclick='sendCommand("adjust-cooldown-ph?v0="+document.getElementById("phAdjustmentCooldownInput").value)'>Set</button></td>
                </tr>
                <tr>
                    <td>PH Test Cooldown (ms)</td><td><input value="%d" id="phTestCooldownInput"><button onclick='sendCommand("test-cooldown-ph?v0="+document.getElementById("phTestCooldownInput").value)'>Set</button></td>
                </tr>
                <tr>
                    <td>Test PH Pumps</td><td><button onclick='sendCommand("lower-ph")'>PH -</button><button onclick='sendCommand("raise-ph")'>PH +</button></td>
                </tr>
            </tbody>
        </table>
    </div>


    <div class="panel">
        <div class="panel-header">
            <h1>Nutrients Settings</h1>
            <div class="horizontal-box">
                <h2>Nutrients Level: %dppm</h2>
                <h2>Status: %s</h2>
            </div>
        </div>
        <table>
            <tbody>
                <tr>
                    <td>Target Nutrients Level (ppm)</td><td><input value="%d" id="targetNutrientsInput"><button onclick='sendCommand("target-nutrients?v0="+document.getElementById("targetNutrientsInput").value)'>Set</button></td>
                </tr>
                <tr>
                    <td>Nutrients Level Tolerance (ppm) +/-</td><td><input value="%d" id="nutrientsToleranceInput"><button onclick='sendCommand("tolerance-nutrients?v0="+document.getElementById("nutrientsToleranceInput").value)'>Set</button></td>
                </tr>
                <tr>
                    <td>Nutrients Adjustment Step (ms)</td><td><input value="%d" id="nutrientsAdjustmentStepInput"><button onclick='sendCommand("step-nutrients?v0="+document.getElementById("nutrientsAdjustmentStepInput").value)'>Set</button></td>
                </tr>
                <tr>
                    <td>Nutrients Adjustment Cooldown (ms)</td><td><input value="%d" id="nutrientsAdjustmentCooldownInput"><button onclick='sendCommand("adjust-cooldown-nutrients?v0="+document.getElementById("nutrientsAdjustmentCooldownInput").value)'>Set</button></td>
                </tr>
                <tr>
                    <td>Nutrients Test Cooldown (ms)</td><td><input value="%d" id="nutrientsTestCooldownInput"><button onclick='sendCommand("test-cooldown-nutrients?v0="+document.getElementById("nutrientsTestCooldownInput").value)'>Set</button></td>
                </tr>
                <tr>
                    <td>Test Nutrients Pumps</td><td><button  onclick='sendCommand("raise-nutrients")'>Pump</button></td>
                </tr>
            </tbody>
        </table>
    </div>
</div>

)