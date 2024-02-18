#include <Arduino.h>
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

</script>

</body>
</html>
)=====";