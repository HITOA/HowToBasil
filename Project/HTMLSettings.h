EMBED_FILE(

<div class="panel-container">
    <div class="panel">
        <div class="panel-header">
            <h1>Wifi Settings</h1>
            <div></div>
            <h2>Connected to wifi : %s</h2>
        </div>
        <table>
            <tbody>
                <tr>
                    <td>*hidden AP will not appear by scan.</td>
                </tr>
                <tr>
                    <td>SSID</td>
                    <td><input id="wifi-ssid" value="wifi-name"></td>
                </tr>
                <tr>
                    <td>Password</td>
                    <td><input id="wifi-password" value="" type="password"></td>
                </tr>
                <tr>
                    <td><button>Scan Networks</button></td>
                    <td><button onclick='sendCommand("connect-wifi?v0=" + document.getElementById("wifi-ssid").value + "&v1=" + document.getElementById("wifi-password").value)'>Connect</button></td>
                </tr>
            </tbody>
        </table>
    </div>
    <div class="panel">
        <div class="panel-header">
            <h1>AP Settings</h1>
            <div></div>
            <h2>Access Point : %s</h2>
        </div>
        <table>
            <tbody>
                <tr>
                    <td>*reset is needed to update any change.</td>
                </tr>
                <tr>
                    <td>SSID</td>
                    <td><input id="ap-ssid" value="%s"></td>
                </tr>
                <tr>
                    <td>Password</td>
                    <td><input id="ap-password" value="%s"></td>
                </tr>
                <tr>
                    <td><button onclick='sendCommand("update-ap-settings?v0=" + document.getElementById("ap-ssid").value + "&v1=" + document.getElementById("ap-password").value)'>Update</button></td>
                </tr>
            </tbody>
        </table>
    </div>
</div>

)