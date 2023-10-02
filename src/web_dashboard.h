#include <Arduino.h>
const char MAIN_page[] PROGMEM = R"=====(
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
  </div>
</nav>


<!-- Overlay effect when opening sidebar on small screens -->
<div class='w3-overlay w3-hide-large w3-animate-opacity' onclick='w3_close()' style='cursor:pointer' title='close side menu' id='myOverlay'></div>

<!-- !PAGE CONTENT! -->
<div class='w3-main' style='margin-left:300px;margin-top:43px;'>

  <!-- Header -->
  <header class='w3-container' style='padding-top:22px'>
    <h5><b><i class='fa fa-chalkboard-user'></i>Virtual Buttons</b></h5>
  </header>

  <div class='w3-row-padding w3-margin-bottom'>
    <!-- button start-->
    <div class='w3-quarter'>
      <div class='w3-container w3-green w3-padding-16'>
        <div class='w3-left'><i class='fa fa-play w3-xxlarge'></i></div>
            <button onclick='event_start_click();' class='w3-button w3-green'>Press Start</button>
      </div>
    </div>
    <!-- button end-->
    <!-- button start-->
    <div class='w3-quarter'>
        <div class='w3-container w3-red w3-padding-16'>
            <div class='w3-left'><i class='fa fa-power-off w3-xxlarge'></i></div>
                <button onclick='event_restart_click();' class='w3-button w3-red'>Restart</button>
        </div>
    </div>
    <!-- button end-->
    <!-- button start-->
    <div class='w3-quarter'>
        <div class='w3-container w3-red w3-padding-16'>
            <div class='w3-left'><i class='fa fa-play w3-xxlarge'></i></div>
                <button onclick='event_outhole_click();' class='w3-button w3-red'>Outhole</button>
        </div>
    </div>
    <!-- button end-->
    <!-- button start-->
    <div class='w3-quarter'>
        <div class='w3-container w3-red w3-padding-16'>
            <div class='w3-left'><i class='fa fa-play w3-xxlarge'></i></div>
                <button onclick='event_rollover_click();' class='w3-button w3-red'>Rollover</button>
        </div>
    </div>
    <!-- button end-->
    
  </div>

  <div class='w3-panel'>
    <div class='w3-row-padding' style='margin:0 -16px'>
      <div class='w3-third'>
        <h5>Machine State</h5>
        <div class='w3-container w3-orange w3-text-white w3-padding-16'>
            <div class='w3-left'><i class='fa fa-gamepad w3-xxxlarge'></i></div>
            <div class='w3-right'>
              <h3><span id='machineState'>Not Read Yet</span></h3>
            </div>
            <div class='w3-clear'></div>
            <h4>Machine State</h4>
          </div>
      </div>
      <div class='w3-twothird'>
        <h5>Stats</h5>
        <table class='w3-table w3-striped w3-bordered w3-border w3-hoverable w3-white'>
          <tr>
            <td><i class='fa fa-microchip w3-text-blue w3-large'></i></td>
            <td>Core Machine Operations</td>
            <td><i><span id='cpu0Hz'>Not Read Yet</span></i></td>
          </tr>
          <tr>
            <td><i class='fa fa-microchip w3-text-red w3-large'></i></td>
            <td>Webserver Operations</td>
            <td><i><span id='cpu1Hz'>Not Read Yet</span></i></td>
          </tr>
          <tr>
            <td><i class='fa fa-user w3-text-red w3-large'></i></td>
            <td>Current Player</td>
            <td><i><span id='playerNumber'>Not Read Yet</span></i></td>
          </tr>
          <tr>
            <td><i class='fa fa-bullseye w3-text-red w3-large'></i></td>
            <td>Ball Number</td>
            <td><i><span id='ballNumber'>Not Read Yet</span></i></td>
          </tr>
          <tr>
            <td><i class='fa fa-bookmark w3-text-red w3-large'></i></td>
            <td>Player Score</td>
            <td><i><span id='playerScore'>Not Read Yet</span></i></td>
          </tr>    
          <tr>
            <td><i class='fa fa-suitcase medical w3-text-red w3-large'></i></td>
            <td>Ball Save Active</td>
            <td><i><span id='ballSave'>Not Read Yet</span></i></td>
          </tr>       
        </table>
      </div>
    </div>
  </div>
  <hr>
  <header class='w3-container w3-blue-grey w3-center'>
    <h2 class='w3-monospace w3-text-red'><span id='topDisplay'></span></h2>
  </header>
    <header class='w3-container w3-blue-grey w3-center'>
    <h2 class='w3-monospace w3-text-red'><span id='bottomDisplay'></span></h2>
  </header>


  <div class='w3-container'>
    <h5>Player Stats</h5>
    <table class='w3-table w3-striped w3-bordered w3-border w3-hoverable w3-white'>
      <tr>  
        <th>No.</th>
        <th>Score</th>
        <th>Ball</th>
      <tr>
        <td>1</td>
        <td><span id='p1score'>0</span></td>
        <td><span id='p1ball'>0</span></td>
      </tr>
      <tr>
        <td>2</td>
        <td><span id='p2score'>0</span></td>
        <td><span id='p2ball'>0</span></td>
      </tr>
      <tr>
        <td>3</td>
        <td><span id='p3score'>0</span></td>
        <td><span id='p3ball'>0</span></td>
      </tr>
      <tr>
        <td>4</td>
        <td><span id='p4score'>0</span></td>
        <td><span id='p4ball'>0</span></td>
      </tr>
    </table>

  <div class='w3-container'>
    <h5>Top Scores</h5>
    <table class='w3-table w3-striped w3-bordered w3-border w3-hoverable w3-white'>
      <tr>
        <td>ASH</td>
        <td>1,000,000</td>
      </tr>
      <tr>
        <td>ASH</td>
        <td>900,000</td>
      </tr>
      <tr>
        <td>ASH</td>
        <td>800,000</td>
      </tr>
      <tr>
        <td>ASH</td>
        <td>700,000</td>
      </tr>
      <tr>
        <td>ASH</td>
        <td>600,000</td>
      </tr>
      <tr>
        <td>ASH</td>
        <td>500,000</td>
      </tr>
      <tr>
        <td>ASH</td>
        <td>450,000</td>
      </tr>
      <tr>
        <td>ASH</td>
        <td>400,000</td>
      </tr>
      <tr>
        <td>ASH</td>
        <td>350,000</td>
      </tr>
      <tr>
        <td>ASH</td>
        <td>300,000</td>
      </tr>
      
    </table>
 <hr>
     <header class='w3-container w3-blue-grey w3-center'>
    <h2>Console Debug Switches</h2>
  </header>   
 <div class='w3-row-padding w3-margin-bottom'>
    <!-- button start-->
    <div class='w3-quarter'>
      <div class='w3-container w3-green w3-padding-16'>
        <div class='w3-left'></div>
            <button onclick='event_debugSwitch_click();' class='w3-button w3-green'>Debug Switches</button>
      </div>
    </div>
    <!-- button end-->
    <!-- button start-->
    <div class='w3-quarter'>
        <div class='w3-container w3-red w3-padding-16'>
            <div class='w3-left'></div>
                <button onclick='event_debugCoil_click();' class='w3-button w3-red'>Debug Coils</button>
        </div>
    </div>
    <!-- button end-->
    <!-- button start-->
    <div class='w3-quarter'>
        <div class='w3-container w3-red w3-padding-16'>
            <div class='w3-left'></div>
                <button onclick='event_debugOps_click();' class='w3-button w3-red'>Debug Ops</button>
        </div>
    </div>
    <!-- button end-->

    
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
  getStatus();
  getCPU0();
  getCPU1();
  getPlayerNumber();
  getBallNumber();
  getPlayerScore();
  getBallSave();
  getTopDisplay();
  getBottomDisplay();
  getP1Score();
  getP1Ball();
  getP2Score();
  getP2Ball();
  getP3Score();
  getP3Ball();
  getP4Score();
  getP4Ball();
}, 1000); //1000mSeconds update rate

function getStatus() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById('machineState').innerHTML =
      this.responseText ;
    }
  };
  xhttp.open('GET', 'ajax_getState', true);
  xhttp.send();
}

function getCPU0() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById('cpu0Hz').innerHTML =
      this.responseText + 'Hz';
    }
  };
  xhttp.open('GET', 'ajax_getCPU0', true);
  xhttp.send();
}

function getCPU1() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById('cpu1Hz').innerHTML =
      this.responseText + 'Hz';
    }
  };
  xhttp.open('GET', 'ajax_getCPU1', true);
  xhttp.send();
}

function getPlayerNumber() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById('playerNumber').innerHTML =
      this.responseText;
    }
  };
  xhttp.open('GET', 'ajax_getPlayerNumber', true);
  xhttp.send();
}

function getBallNumber() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById('ballNumber').innerHTML =
      this.responseText;
    }
  };
  xhttp.open('GET', 'ajax_getBallNumber', true);
  xhttp.send();
}

function getPlayerScore() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById('playerScore').innerHTML =
      this.responseText;
    }
  };
  xhttp.open('GET', 'ajax_getPlayerScore', true);
  xhttp.send();
}

function getBallSave() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById('ballSave').innerHTML =
      this.responseText;
    }
  };
  xhttp.open('GET', 'ajax_getBallSave', true);
  xhttp.send();
}

function getTopDisplay() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById('topDisplay').innerHTML =
      this.responseText;
    }
  };
  xhttp.open('GET', 'ajax_getTopDisplay', true);
  xhttp.send();
}

function getBottomDisplay() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById('bottomDisplay').innerHTML =
      this.responseText;
    }
  };
  xhttp.open('GET', 'ajax_getBottomDisplay', true);
  xhttp.send();
}

function getP1Score() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById('p1score').innerHTML =
      this.responseText;
    }
  };
  xhttp.open('GET', 'ajax_getP1Score', true);
  xhttp.send();
}
function getP2Score() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById('p2score').innerHTML =
      this.responseText;
    }
  };
  xhttp.open('GET', 'ajax_getP2Score', true);
  xhttp.send();
}
function getP3Score() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById('p3score').innerHTML =
      this.responseText;
    }
  };
  xhttp.open('GET', 'ajax_getP3Score', true);
  xhttp.send();
}
function getP4Score() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById('p4score').innerHTML =
      this.responseText;
    }
  };
  xhttp.open('GET', 'ajax_getP4Score', true);
  xhttp.send();
}

function getP1Ball() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById('p1ball').innerHTML =
      this.responseText;
    }
  };
  xhttp.open('GET', 'ajax_getP1Ball', true);
  xhttp.send();
}
function getP2Ball() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById('p2ball').innerHTML =
      this.responseText;
    }
  };
  xhttp.open('GET', 'ajax_getP2Ball', true);
  xhttp.send();
}
function getP3Ball() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById('p3ball').innerHTML =
      this.responseText;
    }
  };
  xhttp.open('GET', 'ajax_getP3Ball', true);
  xhttp.send();
}
function getP4Ball() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById('p4ball').innerHTML =
      this.responseText;
    }
  };
  xhttp.open('GET', 'ajax_getP4Ball', true);
  xhttp.send();
}

function event_start_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/startbutton', true);
    xhttp.send();
}
function event_restart_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/restart', true);
    xhttp.send();
}

function event_outhole_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/outholeswitch', true);
    xhttp.send();
}

function event_rollover_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/rolloverswitch', true);
    xhttp.send();
}

function event_debugSwitch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './debug/switch', true);
    xhttp.send();
}
function event_debugCoil_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './debug/coil', true);
    xhttp.send();
}
function event_debugOps_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './debug/ops', true);
    xhttp.send();
}

</script>

</body>
</html>
)=====";