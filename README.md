# ESP32-Pinball-OS
<h1>Simple Pinball Machine Operating System, designed for the ESP32 chip</h1>

<b>Very early days</b> - this repository is nowhere near release yet, but is actively being worked on.

This repository is created from the whole PlatformIO project on my laptop, however if you want to work in arduino, just download the contents of the <b>src</b> folder and the main program to open is ESP32Pinball.cpp.  I do reccomend installing Visual Studio code and adding the platformIO extension.  Fiddly for the uninitiated but makes things so much easier.

<em>THIS CODE WAS CREATED ON MAC, THIS MEANS IF YOU ARE USING A WINDOWS DEVICE TO BUILD THE FIRMWARE, YOU MAY NEED TO FIND AND REPLACE "/" TO "\" IN THE CODE<em>

For example this is good for Mac
#include "SETTINGS/JSON_settings.h"

and this is good for Windows
#include "SETTINGS\JSON_settings.h"


Based upon the excellent Mishmash Homebrew Pinball found here: <a href="https://www.pinballinfo.com/community/threads/mishmash-self-build-let%E2%80%99s-make-a-pinball-machine.50005/post-451003">Here</a>

Progress on this project also documented here: <a href="https://www.pinballinfo.com/community/threads/mishmash-homebrew-pt-ii.57332/">Here</a>

<h2>Bill of materials</h2><br />
A PCB - you can use the Gerber files in this repository or create your own.  I use 2 x 595 Shift Registers to drive up to 16 MOSFETs which then drive up to 16 coils, you could add more to drive more if needed. <br />

This project uses Arduino C++ and makes use of a ESP32 DevKit v1: <a href="https://www.amazon.co.uk/dp/B076HK8DCN?ref_=cm_sw_r_apan_dp_JYHN494QPACA0QZ0KHBW">Here</a><br/>

4 x SN74HC595N Shift Register <a href="https://www.amazon.co.uk/10-Pack-SN74HC595N-Registers-Integrated-Circuits/dp/B0C349T5XN/ref=sr_1_3?crid=34UUS453QPZ7X&keywords=SN74HC595N+Shift+Register&qid=1699019877&s=electronics&sprefix=sn74hc595n+shift+register%2Celectronics%2C75&sr=1-3-catcorr">Here</a><br />

2 x SN74HC165N Shift Register <a href="https://www.amazon.co.uk/Reland-Sun-SN74HC165N-SN74HC157N-SN74HC161N/dp/B09BFNCG97/ref=sr_1_2?crid=354YY8B0O1KRC&keywords=SN74HC165N%2BShift%2BRegister&qid=1699019932&s=electronics&sprefix=sn74hc165n%2Bshift%2Bregister%2Celectronics%2C153&sr=1-2-catcorr&th=1">Here</a><br />

6 x 16 pin IC Sockets <a href="https://www.amazon.co.uk/16-Pin-DIL-Sockets-Pack/dp/B00KM1O91S/ref=sr_1_2?crid=2ZKVM083D8PRW&keywords=16+pin+chip&qid=1699019985&s=electronics&sprefix=16+pin+chip%2Celectronics%2C119&sr=1-2">Here</a><br />

Assorted Male and Female Dupont Header Pins <a href="https://www.amazon.co.uk/Aussel-6Colors-Breakable-Connector-PIN-6C-60PCS/dp/B078SQ1CZF/ref=sr_1_6?crid=2ITCIHOVTMOAT&keywords=dupont%2Bheader%2Bpins&qid=1699020050&s=electronics&sprefix=dupont%2Bheader%2Bpins%2Celectronics%2C80&sr=1-6&th=1">Here</a><br />

16 x 10k Resistors

To drive solenoids, you will need 

4 x DollaTek 4 Channels 4 Route MOSFET Button IRF540 V2.0 for Arduino <a href="https://www.amazon.co.uk/DollaTek-Channels-MOSFET-Button-Arduino/dp/B07MPB52GC/ref=sr_1_15?crid=2H95ZT40UJE51&keywords=mosfet+board&qid=1699020505&sprefix=mosfet+board%2Caps%2C93&sr=8-15">Here</a><br />

<h2>Theory of operation</h2>
<p>The ESP32 has two cores.  Core 1 is commonly used for the main loop, however we ignore this loop within this project as we will be operating on both cores and utilising interupts on Core 1.</p>

<h3>Core 1</h3>
<ul>
  <li>Interupt every 1 milisecond (1000 times a second).
    <ul>
      <li>Scan the switch matrix for closed switches.</li>
      <li>Add any closed switches to a switch array.</li>
      <li>Check for any energised solenoids that need to be powered off.</li>
    </ul>
  </li>
</ul>
<h3>Core 0</h3>
<li>Thread running a loop checking for leds in the ws2812b strip that need to be acted on.</li>
<li>Thread running a loop checking for closed switches in the switch array that can then be acted on.</li>
<li>Thread running a loop checking for updates to the LCD display that need to be acted on.</li>
<li>Thread running the web server processes. Please note, the operation of a webserver on the same core as the leds causes minor LED issues.  It is expected that once the game is fully configured, web server will be disabled freeing up resources for game operation.</li>

<h3>Classes</h3>
<p>There are several classes that handle some of the foundational functionality of elements of the pinball</p>
<ul>
  <li>Pinball Switch</li>
  <li>Pinball Coil</li>
  <li>Pinball LED</li>
  <li>Pinball Game</li>
  <li>Pinball Audio</li>
</ul>
<p>These classes are instantiated during machine startup based on JSON files loaded from the SPIFFS.</p>

<h3>JSON Settings</h3>
<ul>
  <li>General Settings</li>
  <li>Audio</li>
  <li>Coils</li>
  <li>Switches</li>
  <li>Switch to Coil Bindings</li>
  <li>LEDs</li>
</ul>
<h3>WIFI</h3>
<p>The first time the ESP32 loads up, if it cannot connect to WIFI, it starts its own access point.  Connect to this access point with any device and a captive portal will load and redirect the device browser to http://4.3.2.1 and a web page that allows for your local WIFI to be connected to.</p>
<p>The web server will then be accessible from http://esppos.local.</p>
<p>The web server allows for configuration and testing of your pinball machine, but should not be used once design and testing is complete, this frees resources on the ESP32 for smoother operation of LEDs, Displays and rules.</p>








