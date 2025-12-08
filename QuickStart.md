<h1>Quick Start</h1>
<p>You may wish to try out running the code on an ESP32 before connecting it to a PCB or even soldering to a breadboard - in this case try these steps</p>
<ol>
<li>Set up your development environment.  I used Visual Studio Code with Playform IO</li>
<li>Get a copy of this code and set up a new project</li>
<li>If on a Windows device, replace forward slash symbols with backslash - this is because your operating system will deal with folders differently</li>
<li>Edit the file SETTINGS>globalVariables.h and change the variable webOn to true, then save</li>
<li>You should be able to build and upload the code staight away using a USB cable</li>
<li>Connect your device to the new Wifi called <b>ESP32Pinball-Configure-Me</b></li>
<li>Open browser and you should be redirected to a captive portal</li>
<li>Click Basic Config</li>
<li>Enter your local WifI details, scroll down and click Submit</li>  
<li>The device will rebooyt and should connect to your Wifi.</li>
<li>You can connect to your device over wifi using the address http://esppos.local</li>
<li>Now you have access to the device you can try out some configurations</li>
  <ul>
    <li>The Config Menu gives access to configure the ESP32 pins, the size of the switch matrix in rows and columns</li>
    <li>The Config Switches lets you set up each switch in the switch matrix</li>
    <ul>
      <li>Each switch can have many properties (tbc)</li>
    </ul>
    <li>The Config Coils lets you configure up to 16 coils (however you are free to extend this in the code as needed)</li>
    <li>The Switch Coil Bindings allows you to bind a coils to a switch.  Like a slingshot which may fire as soon as triggered, or a saucer which may fire programatically.</li>
    <li>Config Lighting enables you to pre-configure each led with colour, brightness and flash speed</li>
    <b>Other configurations are still work in progress</b>
    <li>Live View - this gives you access to trigger switches from buttons on the screen.  This is useful for testing rules.</li>
  </ul>
</ol>
