#include <Arduino.h>
const char DOWNLOAD_page[] PROGMEM = R"=====(
  <!-- Header -->
  <header class='w3-container' style='padding-top:22px'>
    <h5><b><i class='fa fa-chalkboard-user'></i>Config Download</b></h5>
  </header>
  <div class="w3-container">
    <div class="w3-padding w3-white w3-display-container">
      <p>Use this page to download config files.</p>
      <p>1. Click Generate Download and wait for a few minutes.</p>
      <p>2. Once Download appears you can click to download.</p>
    </div>
    <div class="w3-section">
        <p>
          <span id="generate" style="display:block;" onclick="generateDownload();">Generate Download<span>
          <span id="proc" style="display:none;">Processing Please Wait<span>
        </p>
        <br>
        <a id="dl" style="display:none;" download="backup.zip"> </a>
    </div>
  </div>
)=====";