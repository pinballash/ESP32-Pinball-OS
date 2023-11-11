#include <Arduino.h>
const char CONFIG_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<title>ESP32 Pinball OS</title>
<meta charset='UTF-8'>
<meta name='viewport' content='width=device-width, initial-scale=1'>
<link rel='stylesheet' href='https://www.w3schools.com/w3css/4/w3.css'>
<link rel='stylesheet' href='https://fonts.googleapis.com/css?family=Raleway'>
<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css'>
<style>
html,body,h1,h2,h3,h4,h5 {font-family: 'Raleway', sans-serif}
</style>
</head>
<body class='w3-light-grey'>

<!-- Top container -->
<div class='w3-bar w3-top w3-black w3-large' style='z-index:4'>
  <button class='w3-bar-item w3-button w3-hide-large w3-hover-none w3-hover-text-light-grey' onclick='w3_open();'><i class='fa fa-bars'></i>  Menu</button>
  <span class='w3-bar-item w3-right'>ESP32 Pinball OS</span>
</div>

<!-- Sidebar/menu -->
<nav class='w3-sidebar w3-collapse w3-white w3-animate-left' style='z-index:3;width:300px;' id='mySidebar'><br>
  <div class='w3-container'>
    <h5>Menu</h5>
  </div>
  <div class='w3-bar-block'>
    <a href='#' class='w3-bar-item w3-button w3-padding-16 w3-hide-large w3-dark-grey w3-hover-black' onclick='w3_close()' title='close menu'><i class='fa fa-remove fa-fw'></i>  Close Menu</a>
    <a href='./viewState' class='w3-bar-item w3-button w3-padding w3-blue'><i class='fa fa-play'></i> Live View</a>
    <a href='./uploadDev' class='w3-bar-item w3-button w3-padding w3-blue'><i class='fa fa-wrench fa-fw'></i>Update</a>
    <a href='./action/solenoidTest' class='w3-bar-item w3-button w3-padding w3-blue'><i class='fa fa-wrench fa-fw'></i>Solenoid Test</a>
	<a href='./config' class='w3-bar-item w3-button w3-padding w3-blue'><i class='fa fa-wrench fa-fw'></i>Config</a>
  </div>
</nav>


<!-- Overlay effect when opening sidebar on small screens -->
<div class='w3-overlay w3-hide-large w3-animate-opacity' onclick='w3_close()' style='cursor:pointer' title='close side menu' id='myOverlay'></div>

<!-- !PAGE CONTENT! -->
<div class='w3-main' style='margin-left:300px;margin-top:43px;'>

  <!-- Header -->
  <header class='w3-container' style='padding-top:22px'>
    <h5><b><i class='fa fa-chalkboard-user'></i>Configuration</b></h5>
  </header>
  <div>
	<code>
	<span id='config'>Not Read Yet</span>
	</code>
  </div>

  <!-- Footer -->
  <footer class='w3-container w3-padding-16 w3-light-grey'>
    <!--<h4>FOOTER</h4>-->
    <!--<p>Powered by <a href='https://www.w3schools.com/w3css/default.asp' target='_blank'>w3.css</a></p>-->
  </footer>

  <!-- End page content -->
</div>

<script>
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

setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getConfig();
}, 1000); //1 Second update rate

function getConfig() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById('config').innerHTML =
      this.responseText ;
    }
  };
  xhttp.open('GET', 'ajax_getConfig', true);
  xhttp.send();
}

</script>

</body>
</html>
)=====";