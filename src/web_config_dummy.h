#include <Arduino.h>
const char CONFIG_DUMMY_page[] PROGMEM = R"=====(
    <!-- Header -->
  <header class='w3-container' style='padding-top:22px'>
    <h5><b><i class='fa fa-chalkboard-user'></i>Dummy Configuration Page</b></h5>
  </header>
  <div>
	<code>
	<span id='config'></span>
	</code>
  </div>
  <div>
	<p>Dummy Content</p>
  </div>
  <!-- Footer -->
  <footer class='w3-container w3-padding-16 w3-light-grey'>
    <!--<h4>FOOTER</h4>-->
    <!--<p>Powered by <a href='https://www.w3schools.com/w3css/default.asp' target='_blank'>w3.css</a></p>-->
  </footer>

  <!-- End page content -->
</div>
)=====";