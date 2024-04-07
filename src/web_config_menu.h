#include <Arduino.h>
const char CONFIG_MENU_page[] PROGMEM = R"=====(
    <!-- Header -->
  <header class='w3-container' style='padding-top:22px'>
    <h5><b><i class='fa fa-chalkboard-user'></i>Configuration Menu</b></h5>
  </header>
  <div>
	<code>
	<span id='config'></span>
	</code>
  </div>
  <div>
    <h6>Switches and Coils</h6>
	  <div class="w3-row">
      <div class="w3-col w3-container m2 w3-red"><a href='./config' class='w3-bar-item w3-button w3-padding w3-red'><i class='fa fa-wrench fa-fw'></i>Basic Config</a></div>
      <div class="w3-col w3-container m2 w3-red"><a href='./config_switches' class='w3-bar-item w3-button w3-padding w3-red'><i class='fa fa-wrench fa-fw'></i>Config Switches</a></div>
      <div class="w3-col w3-container m2 w3-red"><a href='./config_coils' class='w3-bar-item w3-button w3-padding w3-red'><i class='fa fa-wrench fa-fw'></i>Config Coils</a></div>
      <div class="w3-col w3-container m2 w3-red"><a href='./config_switch_coil_binding' class='w3-bar-item w3-button w3-padding w3-red'><i class='fa fa-wrench fa-fw'></i>Config Switch Coil Bindings</a></div>
      <!--<div class="w3-col w3-container m2 w3-red"><p>5</p></div>-->

    </div>
    <h6>Lighting</h6>
    <div class="w3-row">
      <div class="w3-col w3-container m2 w3-blue"><a href='./config_lighting' class='w3-bar-item w3-button w3-padding w3-blue'><i class='fa fa-wrench fa-fw'></i>Config Lighting</a></div>
      <!--<div class="w3-col w3-container m2 w3-blue"><p>2</p></div>
      <div class="w3-col w3-container m2 w3-blue"><p>3</p></div>
      <div class="w3-col w3-container m2 w3-blue"><p>4</p></div>
      <div class="w3-col w3-container m2 w3-blue"><p>5</p></div>-->
 
    </div>

    <h6>Update and Backup</h6>
    <div class="w3-row">
      <div class="w3-col w3-container m2 w3-red"><a href='./uploadDev' class='w3-bar-item w3-button w3-padding w3-red'><i class='fa fa-wrench fa-fw'></i>Update</a></div>
      <div class="w3-col w3-container m2 w3-red"><a href='./downloadConfig' class='w3-bar-item w3-button w3-padding w3-red'><i class='fa fa-wrench fa-fw'></i>Download</a></div>
      <!--<div class="w3-col w3-container m2 w3-red"><p>3</p></div>
      <div class="w3-col w3-container m2 w3-red"><p>4</p></div>
      <div class="w3-col w3-container m2 w3-red"><p>5</p></div>-->

    </div>
    <h6>Display Text</h6>
    <div class="w3-row">
      <div class="w3-col w3-container m2 w3-blue"><a href='./config_titles' class='w3-bar-item w3-button w3-padding w3-blue'><i class='fa fa-wrench fa-fw'></i>Config Titles</a></div>
      <div class="w3-col w3-container m2 w3-blue"><a href='./config_credits' class='w3-bar-item w3-button w3-padding w3-blue'><i class='fa fa-wrench fa-fw'></i>Config Credits</a></div>
      <div class="w3-col w3-container m2 w3-blue"><a href='./config_instructions' class='w3-bar-item w3-button w3-padding w3-blue'><i class='fa fa-wrench fa-fw'></i>Config Instructions</a></div>
      <!--<div class="w3-col w3-container m2 w3-blue"><p>4</p></div>
      <div class="w3-col w3-container m2 w3-blue"><p>5</p></div>-->
 
    </div>
    <h6>Modes and Code</h6>        
    <div class="w3-row">
      <div class="w3-col w3-container m2 w3-red"><a href='./config_modes' class='w3-bar-item w3-button w3-padding w3-red'><i class='fa fa-wrench fa-fw'></i>Config Modes</a></div>
      <!--<div class="w3-col w3-container m2 w3-red"><p>2</p></div>
      <div class="w3-col w3-container m2 w3-red"><p>3</p></div>
      <div class="w3-col w3-container m2 w3-red"><p>4</p></div>
      <div class="w3-col w3-container m2 w3-red"><p>5</p></div>-->

    </div>
    <h6>Tests</h6>
    <div class="w3-row">
      <div class="w3-col w3-container m2 w3-blue"><a href='./action/solenoidTest' class='w3-bar-item w3-button w3-padding w3-blue'><i class='fa fa-wrench fa-fw'></i>Solenoid Test</a></div>
      <div class="w3-col w3-container m2 w3-blue"><a href='./action/diagnostics' class='w3-bar-item w3-button w3-padding w3-blue'><i class='fa fa-wrench fa-fw'></i>Diagnostics Mode</a></div>
      <!--<div class="w3-col w3-container m2 w3-blue"><p>3</p></div>
      <div class="w3-col w3-container m2 w3-blue"><p>4</p></div>
      <div class="w3-col w3-container m2 w3-blue"><p>5</p></div>-->

    </div>
        

  </div>
  <!-- Footer -->
  <footer class='w3-container w3-padding-16 w3-light-grey'>
    <!--<h4>FOOTER</h4>-->
    <!--<p>Powered by <a href='https://www.w3schools.com/w3css/default.asp' target='_blank'>w3.css</a></p>-->
  </footer>

  <!-- End page content -->
</div>
)=====";