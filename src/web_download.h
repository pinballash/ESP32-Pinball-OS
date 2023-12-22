#include <Arduino.h>
const char DOWNLOAD_page[] PROGMEM = R"=====(
  <!-- Header -->
  <header class='w3-container' style='padding-top:22px'>
    <h5><b><i class='fa fa-chalkboard-user'></i>Config Download</b></h5>
  </header>
  <div class="w3-container">
    <div class="w3-padding w3-white w3-display-container">
      <p>Use this page to download config files</p>
    </div>
    <div class="w3-section">
        <p><span onclick="generateDownload();">Generate Download<span></p>
        <br>
        <a id="dl" download="backup.zip">download</a>
    </div>
  </div>
)=====";