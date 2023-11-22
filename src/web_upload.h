#include <Arduino.h>
const char UPLOAD_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<title>ESP32 Pinball OS - Firmware Upload</title>
<meta charset='UTF-8'>
<meta name='viewport' content='width=device-width, initial-scale=1'>
<link rel='stylesheet' href='./css/w3c.css'>
<!--<link rel='stylesheet' href='https://fonts.googleapis.com/css?family=Raleway'>-->
<!--<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css'>-->
<style>
html,body,h1,h2,h3,h4,h5 {font-family: 'Raleway', sans-serif}
</style>
<script src='./js/jquery.js'></script>
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
    <h5><b><i class='fa fa-chalkboard-user'></i>Firmware Upload</b></h5>
  </header>
  <div class="w3-container">
    <div class="w3-padding w3-white w3-display-container">
      <p>Please use the <b>Choose File</b> button tp select a <em>firmware.bin</em> file and click <b>Upload</a>.</p>
      <p><i class="fa-solid fa-circle-exclamation"></i><em>Only use a firmware.bin file from a source you can trust.</em></p> 

    </div>
    <form class="w3-container w3-card-4" method='POST' action='#' enctype='multipart/form-data' id='upload_form'>
      <div class="w3-section">
          <input class="w3-input" type='file' name='update'>
          <input class="w3-input" type='submit' value='Upload'>
      </div>
      <hr/>
    </form>
    <div id='prgCont' class='w3-padding w3-white w3-display-container' style='display:none;'>
      <div class="w3-light-gray">
        <div id='prg' class='w3-green w3-center w3-padding w3-theme' style='width:0%;'></div>
      </div>
    </div>
  </div>
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
$('form').submit(function(e)
{
  e.preventDefault();
  var form = $('#upload_form')[0];
  var data = new FormData(form);
  $.ajax(
  {
    url: '/update',
    type: 'POST',
    data: data,
    contentType: false,
    processData:false,
    xhr: function() 
    {
      var xhr = new window.XMLHttpRequest();
      xhr.upload.addEventListener('progress', function(evt) {
      if (evt.lengthComputable) 
      {
        var per = evt.loaded / evt.total;
        var width = Math.round(per*100);
        var elem = document.getElementById("prg");
        var parElem = document.getElementById("prgCont");   
        parElem.style.display = 'block'; 
        elem.style.width = width + '%'; 
        elem.innerHTML = width * 1  + '%';

      }
      }, false);
      return xhr;
    },
    success:function(d, s) 
    {
      window.location.href = './viewState';

    },
      error: function (a, b, c) {
    }
  });
});
</script>

</body>
</html>
)=====";