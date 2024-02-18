#include <Arduino.h>
const char lightingConfig_script_footer[] PROGMEM = R"=====(
<link rel="stylesheet" href="https://cdn.jsdelivr.net/gh/mdbassit/Coloris@latest/dist/coloris.min.css"/>
<script src="https://cdn.jsdelivr.net/gh/mdbassit/Coloris@latest/dist/coloris.min.js"></script>
<script>
var SelectedRow = 0;
var SelectedColumn = 0;

function loadPage()
{
	//do nothing;
  //prepareMatrix();
}
function prepareMatrix()
{
  for(let j = 0; j < 16; j++)
	{
		for(let i = 0; i < 16; i++)
		{
			//lets work on this cell
			var cellRef = j+"_"+i;
			//alert("Updating Cell Ref: "+cellRef);
			var matrix_cell = document.getElementById(cellRef);
      var ledId = (j * 16) + i;
      loadLEDSettings(j,i);
    }
	}
}

function loadLEDSettings(row,col)
{

  	// Creating a xhttp object
  var ledId = (row * 16) + col;
  let xhttp = new XMLHttpRequest();
  let url = "/api/lighting/config/get";

  // open a connection
  xhttp.open("POST", url, true);

  // Set the request header i.e. which type of content you are sending
  xhttp.setRequestHeader("Content-Type", "application/json");

  // Create a state change callback
  xhttp.onreadystatechange = function () {
      if (xhttp.readyState === 4 && xhttp.status === 200) {

        //we have the led data lets use it
        const json =  this.responseText;
        console.log(json);
        const obj = JSON.parse(json);
        var ledIdInput = document.getElementById('ledId');
        var ledNameInput = document.getElementById('ledName');
        var ledColourInput = document.getElementById('ledColour');
        var ledIsOnInput = document.getElementById('ledIsOn');   
        var ledFlashSpeedInput = document.getElementById('ledFlashSpeed');                     
        
        ledNameInput.value = obj.ledName;
        ledColourInput.value = obj.ledColour;
        document.querySelector('#ledColour').dispatchEvent(new Event('input', { bubbles: true }));
        var cellRef = row+"_"+col;
        var matrix_cell = document.getElementById(cellRef);
        matrix_cell.innerHTML = obj.ledName;
                
        if(obj.ledIsOn == "true")
        {
          ledIsOnInput.checked = true;
        }else{
          ledIsOnInput.checked = false;
        }
        ledFlashSpeedInput.value = obj.ledFlashSpeed;
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

const loadLEDsBtn = document.getElementById('LoadLEDsButton');

loadLEDsBtn.addEventListener('click', (e) => {
	e.preventDefault();
	prepareMatrix();
});

var cols = 0;
var rows = 0;
//we need to get this from the main config
function getConfig() {

}



function selectLED(row,col)
{
	var ledIdInput = document.getElementById('ledId');
	
	
	//we get the led id from the matrix (col * 8)+row
	var ledId = (row * 16) + col;
	ledIdInput.value = ledId;
	
	//other values we can load from JSON
	//to do - program AJAX call to get JSON
  loadLEDSettings(row,col);
  ledEdit_open();
  SelectedRow = row;
  SelectedColumn = col;

}

function updateLED()
{
	var ledIdInput = document.getElementById('ledId').value;
	var ledNameInput = document.getElementById('ledName').value;
	var ledColourInput = document.getElementById('ledColour').value;
	var ledIsOn = document.getElementById('ledIsOn').checked;
  var ledFlashSpeedInput = document.getElementById('ledFlashSpeed').value;
	

	//to do - program AJAX call to send JSON
	if(ledIsOn != true)
	{
		ledIsOn = "false";
	}else{
    ledIsOn= "true";
  }

	
	var ledVar = {
		ledId : ledIdInput,
		ledName : ledNameInput,
		ledColour : ledColourInput,
		ledIsOn : ledIsOn,
    ledFlashSpeed : ledFlashSpeedInput
    }
	//console.log(ledVar);
	//var object = Object.create(ledVar);
	//console.log(object);

	var json = JSON.stringify(ledVar);
	//console.log(json);
	
	///
	// Creating a xhttp object
  let xhttp = new XMLHttpRequest();
  let url = "api/lighting/config/set";

  // open a connection
  xhttp.open("POST", url, true);

  // Set the request header i.e. which type of content you are sending
  xhttp.setRequestHeader("Content-Type", "application/json");

  // Create a state change callback
  xhttp.onreadystatechange = function () {
      if (xhttp.readyState === 4 && xhttp.status === 200) {

          // Print received data from server
          loadLEDSettings(SelectedRow,SelectedColumn);

      }
  };

  // Sending data with the request
  xhttp.send(json);

}

function ledEdit_open() {
  var ledEdit = document.getElementById('ledEdit');
  if (ledEdit.style.display === 'block') {
    //ledEdit.style.display = 'none';
    ledEdit.style.display = 'block';
  } else {
    ledEdit.style.display = 'block';
  }
}

</script>

</body>
</html>
)=====";