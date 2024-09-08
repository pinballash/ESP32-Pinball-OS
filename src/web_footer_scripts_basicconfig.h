#include <Arduino.h>
const char upload_script_footer[] PROGMEM = R"=====(<script>
function loadPage()
{
	//nothing
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
      window.location.href = './config_menu';

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
      document.getElementById('ledPin').value = obj.ledPin;
      document.getElementById('leds').value = obj.leds;

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
  let ledPin = document.getElementById("ledPin");
  let leds = document.getElementById("leds");

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
    "switchMatrixColumns" : switchMatrixColumns.options[switchMatrixColumns.selectedIndex].value,
    "ledPin" : ledPin.value,
    "leds" : leds.value
    });
    console.log(data);

  // Sending data with the request
  xhttp.send(data);
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


function generateDownload()
{
  let generateElement = document.getElementById("generate");
  let processingElement = document.getElementById("proc");
  let downloadElement = document.getElementById("dl");
  generateElement.style.display = 'none';
  processingElement.style.display = 'block';
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      //Debug - schow json contents - uncomment this line
      //document.getElementById('config').innerHTML = this.responseText ;
      //this is all well and good, but we really need to get this json, deserialze it and then use specific value pairs to upsate the UI.
      const json =  this.responseText;
      const obj = JSON.parse(json);

      var keyCount  = Object.keys(obj).length;
      //alert("There are "+keyCount+" files that will be downloaded in a zip - the download link will be ready shortly");

      const urls = Object.values(obj)
      .map((url) => '/api/fs/get?filename=' + url);

      fetchBlobs(urls)
        .then(pack)
        .then((zipFile) => dl.href = URL.createObjectURL(zipFile))
        .then(dl.innerText = "Download Zip Now")

      //processingElement.style.display = 'none';
      downloadElement.style.display = 'block';
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