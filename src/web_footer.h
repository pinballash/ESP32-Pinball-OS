#include <Arduino.h>
const char html_footer[] PROGMEM = R"=====(

     <!-- Footer -->
  <footer class='w3-container w3-padding-16 w3-light-grey'>
    <!--<h4>FOOTER</h4>-->
    <p>Powered by <a href='https://github.com/pinballash/ESP32-Pinball-OS' target='_blank'>ESP32 Pinball OS</a></p>
  </footer>
  <!-- End page content -->
</div>
)=====";

const char upload_script_footer[] PROGMEM = R"=====(<script>
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

const char liveview_script_footer[] PROGMEM = R"=====(
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
function event_leftrolloverswitch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/leftrolloverswitch', true);
    xhttp.send();
}
function event_rightrolloverswitch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/rightrolloverswitch', true);
    xhttp.send();
}
function event_leftflipperswitch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/leftflipperswitch', true);
    xhttp.send();
}
function event_rightflipperswitch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/rightflipperswitch', true);
    xhttp.send();
}
function event_leftslingswitch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/leftslingswitch', true);
    xhttp.send();
}
function event_rightslingswitch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/rightslingswitch', true);
    xhttp.send();
}
function event_leftpopswitch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/leftpopswitch', true);
    xhttp.send();
}
function event_rightpopswitch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/rightpopswitch', true);
    xhttp.send();
}
function event_spinnerswitch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/spinnerswitch', true);
    xhttp.send();
}
function event_leftoutlaneswitch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/leftoutlaneswitch', true);
    xhttp.send();
}
function event_rightoutlaneswitch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/rightoutlaneswitch', true);
    xhttp.send();
}
function event_leftinlaneswitch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/leftinlaneswitch', true);
    xhttp.send();
}
function event_rightinlaneswitch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/rightinlaneswitch', true);
    xhttp.send();
}
function event_lefttoplaneswitch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/lefttoplaneswitch', true);
    xhttp.send();
}
function event_righttoplaneswitch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/righttoplaneswitch', true);
    xhttp.send();
}
function event_centertoplaneswitch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/centertoplaneswitch', true);
    xhttp.send();
}
function event_saucerswitch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/saucerswitch', true);
    xhttp.send();
}
function event_standup1switch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/standup1switch', true);
    xhttp.send();
}
function event_standup2switch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/standup2switch', true);
    xhttp.send();
}
function event_standup3switch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/standup3switch', true);
    xhttp.send();
}
function event_standup4switch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/standup4switch', true);
    xhttp.send();
}
function event_standup5switch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/standup5switch', true);
    xhttp.send();
}
function event_drop1switch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/drop1switch', true);
    xhttp.send();
}
function event_drop2switch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/drop2switch', true);
    xhttp.send();
}
function event_drop3switch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/drop3switch', true);
    xhttp.send();
}
function event_drop4switch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/drop4switch', true);
    xhttp.send();
}
function event_drop5switch_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET', './action/drop5switch', true);
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