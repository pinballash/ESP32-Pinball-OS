#include <Arduino.h>
const char CONFIG_page[] PROGMEM = R"=====(
  <!-- Header -->
  <header class='w3-container' style='padding-top:22px'>
    <h5><b><i class='fa fa-chalkboard-user'></i>Configuration</b></h5>
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

		   <input type="submit" value="Submit" onclick="updateSettings();"><br><br>
		</fieldset>
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