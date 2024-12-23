#include <Arduino.h>
const char switch_score_script_footer[] PROGMEM = R"=====(
<script>

var SelectedRow = 0;
var SelectedColumn = 0;

function loadPage()
{
	document.getElementById('myLoadingOverlay').style.display = 'block';
  getConfig();
  document.getElementById('myLoadingOverlay').style.display = 'none';
}

function loadSwitchScoreSettings(row,col)
{

  var switchId = (col * 8) + row;
	// Creating a xhttp object
  let xhttp = new XMLHttpRequest();
  let url = "/api/switch/score/default/get";

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
        var switchScore = document.getElementById('switchScore');
                
        //switchNameInput.value = obj.switchName;
        var cellRef = row+"_"+col;
        var matrix_cell = document.getElementById(cellRef);
        //matrix_cell.innerHTML = obj.switchName;
        var switchNameInput = document.getElementById('switchName');
        switchNameInput.value = matrix_cell.innerHTML;
        switchScore.value = obj.switchScore;
        
        
		  
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
        var switchScore = document.getElementById('switchScore');
                
        switchNameInput.value = obj.switchName;
        var cellRef = row+"_"+col;
        var matrix_cell = document.getElementById(cellRef);
        matrix_cell.innerHTML = obj.switchName;
        
        switchScore.value = obj.switchScore;
        
        
		  
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
	updateSwitchScore();
});

var cols = 0;
var rows = 0;
//we need to get this from the main config
function getConfig() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      
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
	var switchScore = document.getElementById('switchScore');
	
	//we get the switch id from the matrix (col * 8)+row
	var switchId = (col * 8) + row;
	switchIdInput.value = switchId;
	
	//other values we can load from JSON
	//to do - program AJAX call to get JSON
  loadSwitchScoreSettings(row,col);
  switchEdit_open();
  SelectedRow = row;
  SelectedColumn = col;

}

function updateSwitchScore()
{
	var switchIdInput = document.getElementById('switchId').value;
	var switchNameInput = document.getElementById('switchName').value;
	var switchScore = document.getElementById('switchScore').value;
	
	
  
	var switchVar = {
		switchId : switchIdInput,
		switchName : switchNameInput,
		switchScore : switchScore
    }
	//console.log(switchVar);
	//var object = Object.create(switchVar);
	//console.log(object);

	var json = JSON.stringify(switchVar);
	//console.log(json);
	
	///
	// Creating a xhttp object
  let xhttp = new XMLHttpRequest();
  let url = "/api/switch/score/default/set";

  // open a connection
  xhttp.open("POST", url, true);

  // Set the request header i.e. which type of content you are sending
  xhttp.setRequestHeader("Content-Type", "application/json");

  // Create a state change callback
  xhttp.onreadystatechange = function () {
      if (xhttp.readyState === 4 && xhttp.status === 200) {

          // Print received data from server
          loadSwitchScoreSettings(SelectedRow,SelectedColumn);

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