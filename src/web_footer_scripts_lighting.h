#include <Arduino.h>
const char lightingConfig_script_footer[] PROGMEM = R"=====(<script>
var SelectedRow = 0;
var SelectedColumn = 0;

function loadPage()
{
	//do nothing;
}

function loadLEDSettings(ledId)
{

  	// Creating a xhttp object
  let xhttp = new XMLHttpRequest();
  let url = "/api/lighting/config/get";

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
    "ledId":ledId
	});

  // Sending data with the request
  xhttp.send(data);
	
}

const submitBtn = document.getElementById('submitButton');

submitButton.addEventListener('click', (e) => {
	e.preventDefault();
	updateLED();
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



function selectLED(row,col)
{
	var switchIdInput = document.getElementById('ledId');
	var switchNameInput = document.getElementById('switchName');
	var switchDebounceInput = document.getElementById('switchDebounce');
	var switchIsFlipper = document.getElementById('SwitchIsFlipper');
	var switchIsStart = document.getElementById('SwitchIsFlipper');

	
	//we get the switch id from the matrix (col * 8)+row
	var ledId = (row * 16) + col;
	switchIdInput.value = ledId;
	
	//other values we can load from JSON
	//to do - program AJAX call to get JSON
  loadLEDSettings(ledId);
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

</script>

</body>
</html>
)=====";