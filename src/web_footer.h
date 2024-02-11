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


const char upload_script_footer[] PROGMEM = R"=====(<script>
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

const char config_script_footer[] PROGMEM = R"=====(
<script>
    function loadPage()
{
	getConfig(); //on loading this page, lets get the configuration
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

setInterval(function() {
  // Call a function repetatively with 2 Second interval
  //getConfig();
}, 1000); //1 Second update rate

function getConfig() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      //Debug - schow json contents - uncomment this line
      //document.getElementById('config').innerHTML = this.responseText ;
      //this is all well and good, but we really need to get this json, deserialze it and then use pecific value pairs to upsate the UI.
      const json =  this.responseText;
      const obj = JSON.parse(json);
      document.getElementById('machineNameInput').value = obj.Name;
      document.getElementById('machineVersionInput').value = obj.Version;
      document.getElementById('SSID').value = obj.SSID;
      document.getElementById('SSIDPassword').value = obj.SSIDPassword;
      document.getElementById('osr1latchPin').value = obj.osr1latchPin;
      document.getElementById('osr1clockPin').value = obj.osr1clockPin;
      document.getElementById('osr1dataPin').value = obj.osr1dataPin;
      document.getElementById('osr2latchPin').value = obj.osr2latchPin;
      document.getElementById('osr2clockPin').value = obj.osr2clockPin;
      document.getElementById('osr2dataPin').value = obj.osr2dataPin;
      document.getElementById('osr3latchPin').value = obj.osr3latchPin;
      document.getElementById('osr3clockPin').value = obj.osr3clockPin;
      document.getElementById('osr3dataPin').value = obj.osr3dataPin; 
      document.getElementById('isrload').value = obj.isrload;
      document.getElementById('isrclockEnablePin').value = obj.isrclockEnablePin;
      document.getElementById('isrdataIn').value = obj.isrdataIn;
      document.getElementById('isrclockIn').value = obj.isrclockIn;
      document.getElementById('hvrPin').value = obj.hvrPin;
      document.getElementById('flipper1Pin').value = obj.flipper1Pin;
      document.getElementById('flipper2Pin').value = obj.flipper2Pin;
      document.getElementById('switchMatrixRows').value = obj.switchMatrixRows;
      document.getElementById('switchMatrixColumns').value = obj.switchMatrixColumns;

    }
  };
  xhttp.open('GET', 'ajax_getConfig', true);
  xhttp.send();
}

function updateSettings() 
{
  let machineName = document.getElementById('machineNameInput');
  let machineVersion = document.getElementById('machineVersionInput');
  let SSID = document.getElementById('SSID');
  let SSIDPassword = document.getElementById('SSIDPassword');
  let osr1latchPin = document.getElementById("osr1latchPin");
  let osr1clockPin = document.getElementById("osr1clockPin");
  let osr1dataPin = document.getElementById("osr1dataPin");    
  let osr2latchPin = document.getElementById("osr2latchPin");
  let osr2clockPin = document.getElementById("osr2clockPin");
  let osr2dataPin = document.getElementById("osr2dataPin");
  let osr3latchPin = document.getElementById("osr3latchPin");
  let osr3clockPin = document.getElementById("osr3clockPin");
  let osr3dataPin = document.getElementById("osr3dataPin");
  let isrload = document.getElementById("isrload");
  let isrclockEnablePin = document.getElementById("isrclockEnablePin");
  let isrdataIn = document.getElementById("isrdataIn");
  let isrclockIn = document.getElementById("isrclockIn");
  let hvrPin = document.getElementById("hvrPin");
  let flipper1Pin = document.getElementById("flipper1Pin");
  let flipper2Pin = document.getElementById("flipper2Pin");
  let switchMatrixRows = document.getElementById("switchMatrixRows");
  let switchMatrixColumns = document.getElementById("switchMatrixColumns");

  // Creating a xhttp object
  let xhttp = new XMLHttpRequest();
  let url = "/updateConfig";

  // open a connection
  xhttp.open("POST", url, true);

  // Set the request header i.e. which type of content you are sending
  xhttp.setRequestHeader("Content-Type", "application/json");

  // Create a state change callback
  xhttp.onreadystatechange = function () {
      if (xhttp.readyState === 4 && xhttp.status === 200) {

          // Print received data from server
          document.getElementById('config').innerHTML = this.responseText;

      }
  };

  // Converting JSON data to string
  var data = JSON.stringify({
    "Name": machineName.value, 
    "Version": machineVersion.value, 
    "SSID":SSID.value,
    "SSIDPassword":SSIDPassword.value,
    "osr1latchPin" : osr1latchPin.value,
    "osr1clockPin" : osr1clockPin.value,
    "osr1dataPin" : osr1dataPin.value,
    "osr2latchPin" : osr2latchPin.value,
    "osr2clockPin" : osr2clockPin.value,
    "osr2dataPin" : osr2dataPin.value,
    "osr3latchPin" : osr3latchPin.value,
    "osr3clockPin" : osr3clockPin.value,
    "osr3dataPin" : osr3dataPin.value,
    "isrload" : isrload.value,
    "isrclockEnablePin" : isrclockEnablePin.value,
    "isrdataIn" : isrdataIn.value,
    "isrclockIn" : isrclockIn.value,
    "hvrPin" : hvrPin.value,
    "flipper1Pin" : flipper1Pin.value,
    "flipper2Pin" : flipper2Pin.value,
    "switchMatrixRows" : switchMatrixRows.options[switchMatrixRows.selectedIndex].value,
    "switchMatrixColumns" : switchMatrixColumns.options[switchMatrixColumns.selectedIndex].value
    });

  // Sending data with the request
  xhttp.send(data);
}


</script>

</body>
</html>
)=====";

const char liveview_script_footer[] PROGMEM = R"=====(
<script>
var cols = 0;
var rows = 0;
function loadPage()
{
	 getConfig();
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

function event_trigger_switch(row,col) {
  var switchId = (col * 8) + row;
	// Creating a xhttp object
  let xhttp = new XMLHttpRequest();
  let url = "/action/triggerswitch";

  // open a connection
  xhttp.open("POST", url, true);

  // Set the request header i.e. which type of content you are sending
  xhttp.setRequestHeader("Content-Type", "application/json");

  // Create a state change callback
  xhttp.onreadystatechange = function () {
      if (xhttp.readyState === 4 && xhttp.status === 200) {

        //we have the switch data lets use it
        const json =  this.responseText;
        console.log(json);    
      }
  };

  // Converting JSON data to string
  var data = JSON.stringify({
    "switchId":switchId,
    "col":col,
    "row":row
	});

  // Sending data with the request
  xhttp.send(data);
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
function event_restart_click() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      window.location.href = './viewState';

    }
  };
    xhttp.open('GET', './action/restart', true);
    xhttp.send();
    
}


//we need to get this from the main config
function getConfig() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      //Debug - schow json contents - uncomment this line
      //document.getElementById('config').innerHTML = this.responseText ;
      //this is all well and good, but we really need to get this json, deserialze it and then use pecific value pairs to upsate the UI.
      const json =  this.responseText;
      const obj = JSON.parse(json);

      rows = obj.switchMatrixRows;
      cols = obj.switchMatrixColumns;
      prepareMatrix();

    }
  };
  xhttp.open('GET', 'ajax_getConfig', true);
  xhttp.send();
}
function loadSwitches(row,col)
{

  var switchId = (col * 8) + row;
	// Creating a xhttp object
  let xhttp = new XMLHttpRequest();
  let url = "/api/switch/config/get";

  // open a connection
  xhttp.open("POST", url, true);

  // Set the request header i.e. which type of content you are sending
  xhttp.setRequestHeader("Content-Type", "application/json");

  // Create a state change callback
  xhttp.onreadystatechange = function () {
      if (xhttp.readyState === 4 && xhttp.status === 200) {

        //we have the switch data lets use it
        const json =  this.responseText;
        //console.log(json);
        const obj = JSON.parse(json);

        var cellRef = row+"_"+col;
        var matrix_cell = document.getElementById(cellRef);
        matrix_cell.innerHTML = obj.switchName;
        

		  
      }
  };

  // Converting JSON data to string
  var data = JSON.stringify({
    "switchId":switchId
	});

  // Sending data with the request
  xhttp.send(data);
	
}

function prepareMatrix()
{

  for(let i = 0; i < 8; i++)
	{
		for(let j = 0; j < 8; j++)
		{
			//lets work on this cell
			var cellRef = j+"_"+i;
			//alert("Updating Cell Ref: "+cellRef);
			var matrix_cell = document.getElementById(cellRef);
			if(i < cols)
			{
				if(j < rows)
				{
					var switchId = (i * 8) + j;
					loadSwitches(j,i);
         
					
				}else{
					matrix_cell.innerHTML = "";
          matrix_cell.style.display = 'none';
          matrix_cell.parentElement.style.display = 'none';
				}
			}else
			{
				matrix_cell.innerHTML = "";
        //hide the column
        //console.log("Hiding Column "+(i+2));
        var querySelection = "#switchTable tbody tr th:nth-child("+(i+2)+")";
        //console.log(querySelection);
        document.querySelectorAll(querySelection).forEach(el=>el.style.display = 'none');
        
			}
		
		}
    
	
	}

}


</script>

</body>
</html>
)=====";

const char switchConfig_script_footer[] PROGMEM = R"=====(<script>

var SelectedRow = 0;
var SelectedColumn = 0;

function loadPage()
{
	document.getElementById('myLoadingOverlay').style.display = 'block';
  getConfig();
  document.getElementById('myLoadingOverlay').style.display = 'none';
}

function loadSwitchSettings(row,col)
{

  var switchId = (col * 8) + row;
	// Creating a xhttp object
  let xhttp = new XMLHttpRequest();
  let url = "/api/switch/config/get";

  // open a connection
  xhttp.open("POST", url, true);

  // Set the request header i.e. which type of content you are sending
  xhttp.setRequestHeader("Content-Type", "application/json");

  // Create a state change callback
  xhttp.onreadystatechange = function () {
      if (xhttp.readyState === 4 && xhttp.status === 200) {

        //we have the switch data lets use it
        const json =  this.responseText;
        //console.log(json);
        const obj = JSON.parse(json);
        var switchIdInput = document.getElementById('switchId');
        var switchNameInput = document.getElementById('switchName');
        var switchDebounceInput = document.getElementById('switchDebounce');
        var switchIsFlipper = document.getElementById('switchIsFlipper');
        var switchIsStart = document.getElementById('switchIsStart');
        var switchIsCredit = document.getElementById('switchIsCredit');
        var switchIsOuthole = document.getElementById('switchIsOuthole');                      
        var switchDebug = document.getElementById('switchDebug');
        
        switchNameInput.value = obj.switchName;
        var cellRef = row+"_"+col;
        var matrix_cell = document.getElementById(cellRef);
        matrix_cell.innerHTML = obj.switchName;
        
        switchDebounceInput.value = obj.switchDebounce;
        
        if(obj.switchIsFlipper == "true")
        {
          switchIsFlipper.checked = true;
        }else{
          switchIsFlipper.checked = false;
        }

        if(obj.switchIsStart == "true")
        {
          switchIsStart.checked = true;
        }else{
          switchIsStart.checked = false;
        }

        if(obj.switchIsCredit == "true")
        {
          switchIsCredit.checked = true;
        }else{
          switchIsCredit.checked = false;
        }

        if(obj.switchIsOuthole == "true")
        {
          switchIsOuthole.checked = true;
        }else{
          switchIsOuthole.checked = false;
        }

        if(obj.switchDebug == "true")
        {
          switchDebug.checked = true;
        }else{
          switchDebug.checked = false;
        }
		  
      }
  };

  // Converting JSON data to string
  var data = JSON.stringify({
    "switchId":switchId
	});

  // Sending data with the request
  xhttp.send(data);
	
}

const submitBtn = document.getElementById('submitButton');

submitButton.addEventListener('click', (e) => {
	e.preventDefault();
	updateSwitch();
});

var cols = 0;
var rows = 0;
//we need to get this from the main config
function getConfig() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      //Debug - schow json contents - uncomment this line
      //document.getElementById('config').innerHTML = this.responseText ;
      //this is all well and good, but we really need to get this json, deserialze it and then use pecific value pairs to upsate the UI.
      const json =  this.responseText;
      const obj = JSON.parse(json);

      rows = obj.switchMatrixRows;
      cols = obj.switchMatrixColumns;
      prepareMatrix();

    }
  };
  xhttp.open('GET', 'ajax_getConfig', true);
  xhttp.send();
}

function prepareMatrix()
{

  for(let i = 0; i < 8; i++)
	{
		for(let j = 0; j < 8; j++)
		{
			//lets work on this cell
			var cellRef = j+"_"+i;
			//alert("Updating Cell Ref: "+cellRef);
			var matrix_cell = document.getElementById(cellRef);
			if(i < cols)
			{
				if(j < rows)
				{
					var switchId = (i * 8) + j;
					loadSwitchSettings(j,i);
         
					
				}else{
					matrix_cell.innerHTML = "";
          matrix_cell.style.display = 'none';
          matrix_cell.parentElement.style.display = 'none';
				}
			}else
			{
				matrix_cell.innerHTML = "";
        //hide the column
        //console.log("Hiding Column "+(i+2));
        var querySelection = "#switchTable tbody tr th:nth-child("+(i+2)+")";
        //console.log(querySelection);
        document.querySelectorAll(querySelection).forEach(el=>el.style.display = 'none');
        
			}
		
		}
    
	
	}

}

function selectSwitch(row,col)
{
	var switchIdInput = document.getElementById('switchId');
	var switchNameInput = document.getElementById('switchName');
	var switchDebounceInput = document.getElementById('switchDebounce');
	var switchIsFlipper = document.getElementById('SwitchIsFlipper');
	var switchIsStart = document.getElementById('SwitchIsFlipper');

	
	//we get the switch id from the matrix (col * 8)+row
	var switchId = (col * 8) + row;
	switchIdInput.value = switchId;
	
	//other values we can load from JSON
	//to do - program AJAX call to get JSON
  loadSwitchSettings(row,col);
  switchEdit_open();
  SelectedRow = row;
  SelectedColumn = col;

}

function updateSwitch()
{
	var switchIdInput = document.getElementById('switchId').value;
	var switchNameInput = document.getElementById('switchName').value;
	var switchDebounceInput = document.getElementById('switchDebounce').value;
	var switchIsFlipper = document.getElementById('switchIsFlipper').checked;
  var switchIsStart = document.getElementById('switchIsStart').checked;
  var switchIsCredit = document.getElementById('switchIsCredit').checked;
  var switchIsOuthole = document.getElementById('switchIsOuthole').checked;
	var switchDebug = document.getElementById('switchDebug').checked;
	
  //console.log(switchIsFlipper);
	//to do - program AJAX call to send JSON
	if(switchIsFlipper != true)
	{
		switchIsFlipper = "false";
	}else{
    switchIsFlipper = "true";
  }

	if(switchIsStart != true)
	{
		switchIsStart = "false";
	}else{
    switchIsStart = "true";
  }

	if(switchIsCredit != true)
	{
		switchIsCredit = "false";
	}else{
    switchIsCredit = "true";
  }

	if(switchIsOuthole != true)
	{
		switchIsOuthole = "false";
	}else{
    switchIsOuthole = "true";
  }  


	if(switchDebug != true)
	{
		switchDebug = "false";
	}else{
    switchDebug = "true";
  }
	var switchVar = {
		switchId : switchIdInput,
		switchName : switchNameInput,
		switchDebounce : switchDebounceInput,
		switchIsFlipper : switchIsFlipper,
    switchIsStart : switchIsStart,
    switchIsCredit : switchIsCredit,
    switchIsOuthole : switchIsOuthole,
		switchDebug : switchDebug
    }
	//console.log(switchVar);
	//var object = Object.create(switchVar);
	//console.log(object);

	var json = JSON.stringify(switchVar);
	//console.log(json);
	
	///
	// Creating a xhttp object
  let xhttp = new XMLHttpRequest();
  let url = "api/switch/config/set";

  // open a connection
  xhttp.open("POST", url, true);

  // Set the request header i.e. which type of content you are sending
  xhttp.setRequestHeader("Content-Type", "application/json");

  // Create a state change callback
  xhttp.onreadystatechange = function () {
      if (xhttp.readyState === 4 && xhttp.status === 200) {

          // Print received data from server
          loadSwitchSettings(SelectedRow,SelectedColumn);

      }
  };

  // Sending data with the request
  xhttp.send(json);

}

function switchEdit_open() {
  var SwitchEdit = document.getElementById('SwitchEdit');
  if (SwitchEdit.style.display === 'block') {
    //SwitchEdit.style.display = 'none';
    SwitchEdit.style.display = 'block';
  } else {
    SwitchEdit.style.display = 'block';
  }
}



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

const char coilConfig_script_footer[] PROGMEM = R"=====(<script>

var SelectedRow = 0;
var SelectedColumn = 0;

function loadPage()
{
	 document.getElementById('myLoadingOverlay').style.display = 'block';
  getConfig();
   document.getElementById('myLoadingOverlay').style.display = 'none';

}

function loadcoilSettings(row,col)
{

  var coilId = (col * 8) + row;
	// Creating a xhttp object
  let xhttp = new XMLHttpRequest();
  let url = "/api/coil/config/get";

  // open a connection
  xhttp.open("POST", url, true);

  // Set the request header i.e. which type of content you are sending
  xhttp.setRequestHeader("Content-Type", "application/json");

  // Create a state change callback
  xhttp.onreadystatechange = function () {
      if (xhttp.readyState === 4 && xhttp.status === 200) {

        //we have the coil data lets use it
        const json =  this.responseText;
        //console.log(json);
        const obj = JSON.parse(json);
        var coilIdInput = document.getElementById('coilId');
        var coilNameInput = document.getElementById('coilName');
        var shiftRegister = document.getElementById('shiftRegister');
        var shiftRegisterBit = document.getElementById('shiftRegisterBit');
        var pulseTime = document.getElementById('pulseTime');
        var pulseBackOff = document.getElementById('pulseBackOff');

        coilNameInput.value = obj.coilName;
        var cellRef = row+"_"+col;
        var matrix_cell = document.getElementById(cellRef);
        matrix_cell.innerHTML = obj.coilName;
        
       
        pulseTime.value = obj.pulseTime;
        pulseBackOff.value = obj.pulseBackOff;
        

		  
      }
  };

  // Converting JSON data to string
  var data = JSON.stringify({
    "coilId":coilId
	});

  // Sending data with the request
  xhttp.send(data);
	
}

const submitBtn = document.getElementById('submitButton');

submitButton.addEventListener('click', (e) => {
	e.preventDefault();
	updatecoil();
});

var cols = 2;
var rows = 8;
//we need to get this from the main config
function getConfig() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      //Debug - schow json contents - uncomment this line
      //document.getElementById('config').innerHTML = this.responseText ;
      //this is all well and good, but we really need to get this json, deserialze it and then use pecific value pairs to upsate the UI.
      const json =  this.responseText;
      const obj = JSON.parse(json);

      //rows = obj.coilMatrixRows;
      //cols = obj.coilMatrixColumns;
      prepareMatrix();

    }
  };
  xhttp.open('GET', 'ajax_getConfig', true);
  xhttp.send();
}

function prepareMatrix()
{
  for(let i = 0; i < 2; i++)
	{
		for(let j = 0; j < 8; j++)
		{
			//lets work on this cell
			var cellRef = j+"_"+i;
			//alert("Updating Cell Ref: "+cellRef);
			var matrix_cell = document.getElementById(cellRef);
			if(i < cols)
			{
				if(j < rows)
				{
					var coilId = (i * 8) + j;
					loadcoilSettings(j,i);
         
					
				}else{
					matrix_cell.innerHTML = "";
          matrix_cell.style.display = 'none';
          matrix_cell.parentElement.style.display = 'none';
				}
			}else
			{
				matrix_cell.innerHTML = "";
        //hide the column
        //console.log("Hiding Column "+(i+2));
        var querySelection = "#coilTable tbody tr th:nth-child("+(i+2)+")";
        //console.log(querySelection);
        document.querySelectorAll(querySelection).forEach(el=>el.style.display = 'none');
        
			}
		
		}
	
	}
 

}

function selectCoil(row,col)
{
  var coilIdInput = document.getElementById('coilId');
  var coilNameInput = document.getElementById('coilName');
  var shiftRegister = document.getElementById('shiftRegister');
  var shiftRegisterBit = document.getElementById('shiftRegisterBit');
  var pulseTime = document.getElementById('pulseTime');
  var pulseBackOff = document.getElementById('pulseBackOff');

	
	//we get the coil id from the matrix (col * 8)+row
	var coilId = (col * 8) + row;
	coilIdInput.value = coilId;
	shiftRegister.value = col;
  shiftRegisterBit.value = row;
	//other values we can load from JSON
	//to do - program AJAX call to get JSON
  loadcoilSettings(row,col);
  coilEdit_open();
  SelectedRow = row;
  SelectedColumn = col;

}

function updatecoil()
{
  var coilIdInput = document.getElementById('coilId').value;
  var coilNameInput = document.getElementById('coilName').value;
  var shiftRegisterInput = document.getElementById('shiftRegister').value;
  var shiftRegisterBitInput = document.getElementById('shiftRegisterBit').value;
  var pulseTimeInput = document.getElementById('pulseTime').value;
  var pulseBackOffInput = document.getElementById('pulseBackOff').value;

  //console.log(coilIsFlipper);
	//to do - program AJAX call to send JSON

	var coilVar = {
		coilId : coilIdInput,
		coilName : coilNameInput,
    shiftRegister : shiftRegisterInput,
    shiftRegisterBit : shiftRegisterBitInput,
    pulseTime : pulseTimeInput,
    pulseBackOff : pulseBackOffInput
    }

	var json = JSON.stringify(coilVar);

	///
	// Creating a xhttp object
  let xhttp = new XMLHttpRequest();
  let url = "api/coil/config/set";

  // open a connection
  xhttp.open("POST", url, true);

  // Set the request header i.e. which type of content you are sending
  xhttp.setRequestHeader("Content-Type", "application/json");

  // Create a state change callback
  xhttp.onreadystatechange = function () {
      if (xhttp.readyState === 4 && xhttp.status === 200) {

          // Print received data from server
          loadcoilSettings(SelectedRow,SelectedColumn);

      }
  };

  // Sending data with the request
  xhttp.send(json);

}

function coilEdit_open() {
  var coilEdit = document.getElementById('coilEdit');
  if (coilEdit.style.display === 'block') {
    //coilEdit.style.display = 'none';
    coilEdit.style.display = 'block';
  } else {
    coilEdit.style.display = 'block';
  }
}



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

const char switchCoilBindingConfig_script_footer[] PROGMEM = R"=====(<script>

var SelectedRow = 0;
var SelectedColumn = 0;

function loadPage()
{
	document.getElementById('myLoadingOverlay').style.display = 'block';
  getConfig();
  updateCoilOptionNames();
  document.getElementById('myLoadingOverlay').style.display = 'none';
}

function selectElement(id, valueToSelect) {
  if(valueToSelect)
  {
    let element = document.getElementById(id);
    var selectedId = Number(valueToSelect)+1;
    element.selectedIndex = selectedId;
  }
}

function loadSwitches(row,col)
{

  var switchId = (col * 8) + row;
	// Creating a xhttp object
  let xhttp = new XMLHttpRequest();
  let url = "/api/switch/config/get";

  // open a connection
  xhttp.open("POST", url, true);

  // Set the request header i.e. which type of content you are sending
  xhttp.setRequestHeader("Content-Type", "application/json");

  // Create a state change callback
  xhttp.onreadystatechange = function () {
      if (xhttp.readyState === 4 && xhttp.status === 200) {

        //we have the switch data lets use it
        const json =  this.responseText;
        //console.log(json);
        const obj = JSON.parse(json);

        var cellRef = row+"_"+col;
        var matrix_cell = document.getElementById(cellRef);
        matrix_cell.innerHTML = obj.switchName;
        

		  
      }
  };

  // Converting JSON data to string
  var data = JSON.stringify({
    "switchId":switchId
	});

  // Sending data with the request
  xhttp.send(data);
	
}


function loadSwitchSettings(row,col)
{

  deselectAllBindings();
  var switchId = (col * 8) + row;
	// Creating a xhttp object
  let xhttp = new XMLHttpRequest();
  let url = "/api/switch/coil/config/get";

  // open a connection
  xhttp.open("POST", url, true);

  // Set the request header i.e. which type of content you are sending
  xhttp.setRequestHeader("Content-Type", "application/json");

  // Create a state change callback
  xhttp.onreadystatechange = function () {
      if (xhttp.readyState === 4 && xhttp.status === 200) {

        //we have the switch data lets use it
        const json =  this.responseText;
        //console.log(json);
        const obj = JSON.parse(json);
        var switchIdInput = document.getElementById('switchId');
        var switchNameInput = document.getElementById('switchName');
        var instantCoilFireInput = document.getElementById('instantCoilFire');
        
        switchIdInput.innerHTML = obj.switchId;
        
        var cellRef = row+"_"+col;
        var matrix_cell = document.getElementById(cellRef);
        switchNameInput.innerHTML = matrix_cell.innerHTML;

        selectElement("boundCoil", obj.coilBinding);
        if(obj.instantCoilFire == "true")
        {
          instantCoilFireInput.checked = true;
        }else{
          instantCoilFireInput.checked = false;
        }
		  
      }
  };

  // Converting JSON data to string
  var data = JSON.stringify({
    "switchId":switchId
	});

  // Sending data with the request
  xhttp.send(data);
	
}

const submitBtn = document.getElementById('submitButton');

submitButton.addEventListener('click', (e) => {
	e.preventDefault();
	updateSwitch();
});

var cols = 0;
var rows = 0;

//we need to get this from the main config
function getConfig() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      //Debug - schow json contents - uncomment this line
      //document.getElementById('config').innerHTML = this.responseText ;
      //this is all well and good, but we really need to get this json, deserialze it and then use pecific value pairs to upsate the UI.
      const json =  this.responseText;
      const obj = JSON.parse(json);

      rows = obj.switchMatrixRows;
      cols = obj.switchMatrixColumns;
      prepareMatrix();

    }
  };
  xhttp.open('GET', 'ajax_getConfig', true);
  xhttp.send();
}

function deselectAllBindings()
{
 
  var elements = document.getElementById('boundCoil').options;

  for(var i = 0; i < elements.length; i++){
    elements[i].selected = false;
  }

}

function updateCoilOptionNames(){
  var elements = document.getElementById('boundCoil').options;
  for(var i = 0; i < elements.length-1; i++){
    getCoilName(i);
  }
}

function prepareMatrix()
{

  for(let i = 0; i < 8; i++)
	{
		for(let j = 0; j < 8; j++)
		{
			//lets work on this cell
			var cellRef = j+"_"+i;
			//alert("Updating Cell Ref: "+cellRef);
			var matrix_cell = document.getElementById(cellRef);
			if(i < cols)
			{
				if(j < rows)
				{
					var switchId = (i * 8) + j;
					loadSwitches(j,i);
         
					
				}else{
					matrix_cell.innerHTML = "";
          matrix_cell.style.display = 'none';
          matrix_cell.parentElement.style.display = 'none';
				}
			}else
			{
				matrix_cell.innerHTML = "";
        //hide the column
        //console.log("Hiding Column "+(i+2));
        var querySelection = "#switchTable tbody tr th:nth-child("+(i+2)+")";
        //console.log(querySelection);
        document.querySelectorAll(querySelection).forEach(el=>el.style.display = 'none');
        
			}
		
		}
    
	
	}

}

function getCoilName(id)
{
  var coilName = id+" - Undefined";


  var coilId = id;
	// Creating a xhttp object
  let xhttp = new XMLHttpRequest();
  let url = "/api/coil/config/get";

  // open a connection
  xhttp.open("POST", url, true);

  // Set the request header i.e. which type of content you are sending
  xhttp.setRequestHeader("Content-Type", "application/json");

  // Create a state change callback
  xhttp.onreadystatechange = function () {
      if (xhttp.readyState === 4 && xhttp.status === 200) {

        //we have the coil data lets use it
        const json =  this.responseText;
        //console.log(json);
        const obj = JSON.parse(json);
        coilName = id+" - "+ obj.coilName;
        updateOption(id,coilName);
      }
  };

  // Converting JSON data to string
  var data = JSON.stringify({
    "coilId":coilId
	});

  // Sending data with the request
  xhttp.send(data);
}

function updateOption(id,text)
{
  document.getElementById('coil_'+id).text = text;
}

function selectSwitch(row,col)
{
	
	//we get the switch id from the matrix (col * 8)+row
	var switchId = (col * 8) + row;
	document.getElementById('switchId').innerHTML = switchId;
	
	//other values we can load from JSON
	//to do - program AJAX call to get JSON
  loadSwitchSettings(row,col);
  switchEdit_open();
  SelectedRow = row;
  SelectedColumn = col;

}

function updateSwitch()
{
	var switchIdInput = document.getElementById('switchId').innerHTML;
  var coilBinding = document.getElementById('boundCoil').value;
  var instantCoilFireInput = document.getElementById('instantCoilFire').checked
	
  if(instantCoilFireInput != true)
	{
		instantCoilFireInput = "false";
	}else{
    instantCoilFireInput = "true";
  }

	var switchVar = {
		switchId : switchIdInput,
		coilBinding : coilBinding,
    instantCoilFire : instantCoilFireInput
    }

	var json = JSON.stringify(switchVar);

	// Creating a xhttp object
  let xhttp = new XMLHttpRequest();
  let url = "api/switch/coil/config/set";

  // open a connection
  xhttp.open("POST", url, true);

  // Set the request header i.e. which type of content you are sending
  xhttp.setRequestHeader("Content-Type", "application/json");

  // Create a state change callback
  xhttp.onreadystatechange = function () {
      if (xhttp.readyState === 4 && xhttp.status === 200) {

          // Print received data from server
          loadSwitchSettings(SelectedRow,SelectedColumn);

      }
  };

  // Sending data with the request
  xhttp.send(json);

}

function switchEdit_open() {
  var SwitchEdit = document.getElementById('SwitchEdit');
  if (SwitchEdit.style.display === 'block') {
    //SwitchEdit.style.display = 'none';
    SwitchEdit.style.display = 'block';
  } else {
    SwitchEdit.style.display = 'block';
  }
}



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

const char download_script_footer[] PROGMEM = R"=====(
<!-- using JSZip library https://stuk.github.io/jszip/ -->
<script src="https://cdnjs.cloudflare.com/ajax/libs/jszip/3.2.0/jszip.min.js"></script>

<script>
function loadPage()
{
	//do nothing
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

function generateDownload()
{
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      //Debug - schow json contents - uncomment this line
      //document.getElementById('config').innerHTML = this.responseText ;
      //this is all well and good, but we really need to get this json, deserialze it and then use specific value pairs to upsate the UI.
      const json =  this.responseText;
      const obj = JSON.parse(json);

      var keyCount  = Object.keys(obj).length;
      alert("There are "+keyCount+" files that will be downloaded in a zip - the download link will be ready shortly");

      const urls = Object.values(obj)
      .map((url) => '/api/fs/get?filename=' + url);

      fetchBlobs(urls)
        .then(pack)
        .then((zipFile) => dl.href = URL.createObjectURL(zipFile));

    }
  };
  xhttp.open('GET', 'api/fs/list', true);
  xhttp.send();
}


function fetchBlobs(urls) {
  return Promise.all(
    urls.map((url) =>
      fetch(url)
      .then((resp) => resp.blob())
      .then((blob) => {
        // store the file name
        //alert("fetching "+url)
        blob.name = url.slice(url.lastIndexOf('=') + 1)
        //alert("blob name is "+blob.name)
        return blob;
      })
    )
  );
}
function pack(blobs) {
  const zip = new JSZip();
  const folder = zip.folder('configs');
  blobs.forEach((blob) => folder.file(blob.name, blob));
  return zip.generateAsync({type : "blob"});
}






</script>
</body>
</html>
)=====";