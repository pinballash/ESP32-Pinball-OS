#include <Arduino.h>
const char html_footer[] PROGMEM = R"=====(

     <!-- Footer -->

  <footer class='w3-container w3-padding-16 w3-light-grey'>
    <!--<h4>FOOTER</h4>-->
    <p>Powered by <a href='https://github.com/pinballash/ESP32-Pinball-OS' target='_blank'>ESP32 Pinball OS</a></p>
  </footer>
  <!-- End page content -->
</div>
<script>// Get the Sidebar
var mySidebar = document.getElementById('mySidebar');

// Get the DIV with overlay effect
var overlayBg = document.getElementById('myOverlay');

// Toggle between showing and hiding the sidebar, and add overlay effect
function w3_open() {
  if (mySidebar.style.display === 'block') {
    mySidebar.style.display = 'none';
    overlayBg.style.display = 'none';
  } else {
    mySidebar.style.display = 'block';
    overlayBg.style.display = 'block';
  }
}

// Close the sidebar with the close button
function w3_close() {
  mySidebar.style.display = 'none';
  overlayBg.style.display = 'none';
}
</script>
)=====";

const char dummy_script_footer[] PROGMEM = R"=====(<script>
function loadPage()
{
	//nothing
}
// Get the Sidebar
var mySidebar = document.getElementById('mySidebar');

// Get the DIV with overlay effect
var overlayBg = document.getElementById('myOverlay');

// Toggle between showing and hiding the sidebar, and add overlay effect
function w3_open() {
  if (mySidebar.style.display === 'block') {
    mySidebar.style.display = 'none';
    overlayBg.style.display = 'none';
  } else {
    mySidebar.style.display = 'block';
    overlayBg.style.display = 'block';
  }
}

// Close the sidebar with the close button
function w3_close() {
  mySidebar.style.display = 'none';
  overlayBg.style.display = 'none';
}
</script>

</body>
</html>
)=====";
