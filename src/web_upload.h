#include <Arduino.h>
const char UPLOAD_page[] PROGMEM = R"=====(
  <!-- Header -->
  <header class='w3-container' style='padding-top:22px'>
    <h5><b><i class='fa fa-chalkboard-user'></i>Firmware Upload</b></h5>
  </header>
  <div class="w3-container">
    <div class="w3-padding w3-white w3-display-container">
      <p>Please use the <b>Choose File</b> button to select a <em>firmware.bin</em> file and click <b>Upload</b>.</p>
      <p><i class="fa-solid fa-circle-exclamation"></i><em>Only use a firmware.bin file from a source you can trust.</em></p> 

    </div>
    <form class="w3-container w3-card-4" method='POST' action='#' enctype='multipart/form-data' id='upload_form'>
      <div class="w3-section">
          <input class="w3-input" type='file' name='update' accept=".bin" />
          <input class="w3-input" type='submit' value='Upload' />
      </div>
      <hr/>
    </form>
    <div id='prgCont' class='w3-padding w3-white w3-display-container' style='display:none;'>
      <div class="w3-light-gray">
        <div id='prg' class='w3-green w3-center w3-padding w3-theme' style='width:0%;'></div>
      </div>
    </div>

  </div>
)=====";