#include <Arduino.h>
const char CONFIG_page[] PROGMEM = R"=====(
  <!-- Header -->
  <header class='w3-container' style='padding-top:22px'>
    <h5><b><i class='fa fa-chalkboard-user'></i>Basic Configuration</b></h5>
  </header>
  <div>
	<code>
	<span id='config'></span>
	</code>
  </div>
  <div>
	<form class="generated-form"  method="POST" action="#" enctype="multipart/form-data" target="_self">
		<fieldset>
		  <legend> Machine Parameters:: </legend>
		   <label for="text">Machine Name:</label><br>
		   <input type="text" id="machineNameInput" name="machineNameInput"</label><br>
        <label for="text">Machine Version:</label><br>
		   <input type="text" id="machineVersionInput" name="machineVersionInput"><br>

      <label for="text">Wi-Fi SSID:</label><br>
		   <input type="text" id="SSID" name="SSID"><br>

      <label for="text">Wi-Fi Password:</label><br>
		   <input type="password" id="SSIDPassword" name="SSIDPassword"><br>

		   
		</fieldset>
    <fieldset>
		  <legend> ESP32 Pin Definitions:: </legend>
      <table>

      <tr>
          <td colspan="2"><h5>Connections to 74HC595 - Switch Matrix Output Shift Register</h5></td>
        </tr>
        <tr>
          <td>osr1latchPin</td>
          <td><input type="text" id="osr1latchPin" name="osr1latchPin" value="" maxlength="2" size="2"></td>
        </tr>
        <tr>
          <td>osr1clockPin</td>
          <td><input type="text" id="osr1clockPin" name="osr1clockPin" value="" maxlength="2" size="2"></td>
        </tr>
        <tr>
          <td>osr1dataPin</td>
          <td><input type="text" id="osr1dataPin" name="osr1dataPin" value="" maxlength="2" size="2"></td>
        </tr>
        <tr>
          <td colspan="2"><h5>Connections to 74HC595 - Audio Output Shift Register</h5></td>
        </tr>
        <tr>
          <td>osr2latchPin</td>
          <td><input type="text" id="osr2latchPin" name="osr2latchPin" value="" maxlength="2" size="2"></td>
        </tr>
        <tr>
          <td>osr2clockPin</td>
          <td><input type="text" id="osr2clockPin" name="osr2clockPin" value="" maxlength="2" size="2"></td>
        </tr>
        <tr>
          <td>osr2dataPin</td>
          <td><input type="text" id="osr2dataPin" name="osr2dataPin" value="" maxlength="2" size="2"></td>
        </tr>
        <tr>
          <td colspan="2"><h5>Connections to 74HC595 - Coil Output Shift Registers</h5></td>
        </tr>
        <tr>
          <td>osr3latchPin</td>
          <td><input type="text" id="osr3latchPin" name="osr3latchPin" value="" maxlength="2" size="2"></td>
        </tr>
        <tr>
          <td>osr3clockPin</td>
          <td><input type="text" id="osr3clockPin" name="osr3clockPin" value="" maxlength="2" size="2"></td>
        </tr>
        <tr>
          <td>osr3dataPin</td>
          <td><input type="text" id="osr3dataPin" name="osr3dataPin" value="" maxlength="2" size="2"></td>
        </tr>
        <tr>
          <td colspan="2"><h5>Connections to 74HC165 - Input Shift Registers (Audio and Switch Matrix)</h5></td>
        </tr>
        <tr>
          <td>isrload</td>
          <td><input type="text" id="isrload" name="isrload" value="" maxlength="2" size="2"></td>
        </tr>
        
        <tr>
          <td>isrclockEnablePin</td>
          <td><input type="text" id="isrclockEnablePin" name="isrclockEnablePin" value="" maxlength="2" size="2"></td>
        </tr>
        <tr>
          <td>isrdataIn</td>
          <td><input type="text" id="isrdataIn" name="isrdataIn" value="" maxlength="2" size="2"></td>
        </tr>
        <tr>
          <td>isrclockIn</td>
          <td><input type="text" id="isrclockIn" name="isrclockIn" value="" maxlength="2" size="2"></td>
        </tr>
        <tr>
          <td colspan="2"><h5>High Voltage Relay pin</h5></td>
        </tr>
        <tr>
          <td>hvrPin</td>
          <td><input type="text" id="hvrPin" name="hvrPin" value="" maxlength="2" size="2"></td>
        </tr>
        <tr>
          <td colspan="2"><h5>Flippers</h5></td>
        </tr>
        <tr>
          <td>flipper1Pin</td>
          <td><input type="text" id="flipper1Pin" name="flipper1Pin" value="" maxlength="2" size="2"></td>
        </tr>
        <tr>
          <td>flipper2Pin</td>
          <td><input type="text" id="flipper2Pin" name="flipper2Pin" value="" maxlength="2" size="2"></td>
        </tr>
        <tr>
          <td colspan="2"><h65>Led Settings</h5></td>
        </tr>
        <tr>
          <td>ledPin</td>
          <td><input type="text" id="ledPin" name="ledPin" value="" maxlength="2" size="2"></td>
        </tr>
        <tr>
          <td>led count</td>
          <td><input type="text" id="leds" name="leds" value="" maxlength="2" size="2"></td>
        </tr>
       
		  </table>
		   
		</fieldset>
    <fieldset>
		  <legend> Switch Matrix Definitions:: </legend>
      <table>

        <tr>
          <td colspan="2"><h5>Define the number of Rows and Columns in the Matrix</h5></td>
        </tr>
        <tr>
          <td>Rows</td>
          <td>
            <select id="switchMatrixRows" name="switchMatrixRows">
              <option value="0">0</option>
              <option value="1">1</option>
              <option value="2">2</option>
              <option value="3">3</option>
              <option value="4">4</option>
              <option value="5">5</option>
              <option value="6">6</option>
              <option value="7">7</option>
              <option value="8">8</option>
            <select>
          </td>
        </tr>
        <tr>
          <td>Columns</td>
          <td>
            <select id="switchMatrixColumns" name="switchMatrixColumns">
              <option value="0">0</option>
              <option value="1">1</option>
              <option value="2">2</option>
              <option value="3">3</option>
              <option value="4">4</option>
              <option value="5">5</option>
              <option value="6">6</option>
              <option value="7">7</option>
              <option value="8">8</option>
            <select>
          </td>
        </tr>
		  </table>
		   
		</fieldset>
    <input type="submit" value="Submit" onclick="updateSettings();"> Updating Settings will restart the machine.<br><br>
	</form>
  </div>

  <!-- Footer -->
  <footer class='w3-container w3-padding-16 w3-light-grey'>
    <!--<h4>FOOTER</h4>-->
    <!--<p>Powered by <a href='https://www.w3schools.com/w3css/default.asp' target='_blank'>w3.css</a></p>-->
  </footer>

  <!-- End page content -->
</div>


)=====";