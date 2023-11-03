# ESP32-Pinball-OS
Simple Pinball Machine Operating System, designed for the ESP32 chip

Based upon the excellent Mishmash Homebrew Pinball found here: <a href="https://www.pinballinfo.com/community/threads/mishmash-self-build-let%E2%80%99s-make-a-pinball-machine.50005/post-451003">Here</a>

Progress on this project also documented here: <a href="https://www.pinballinfo.com/community/threads/mishmash-homebrew-pt-ii.57332/">Here</a>

<b>Bill of materials</b><br />
A PCB - you can use the Gerber files in this repository or create your own.  I use 2 x 595 Shift Registers to drive up to 16 MOSFETs which then drive up to 16 coils, you could add more to drive more if needed. 

This project uses Arduino C++ and makes use of a ESP32 DevKit v1: <a href="https://www.amazon.co.uk/dp/B076HK8DCN?ref_=cm_sw_r_apan_dp_JYHN494QPACA0QZ0KHBW">Here</a>

4 x SN74HC595N Shift Register <a href="https://www.amazon.co.uk/10-Pack-SN74HC595N-Registers-Integrated-Circuits/dp/B0C349T5XN/ref=sr_1_3?crid=34UUS453QPZ7X&keywords=SN74HC595N+Shift+Register&qid=1699019877&s=electronics&sprefix=sn74hc595n+shift+register%2Celectronics%2C75&sr=1-3-catcorr">Here</a>

2 x SN74HC165N Shift Register <br/>(https://www.amazon.co.uk/Reland-Sun-SN74HC165N-SN74HC157N-SN74HC161N/dp/B09BFNCG97/ref=sr_1_2?crid=354YY8B0O1KRC&keywords=SN74HC165N%2BShift%2BRegister&qid=1699019932&s=electronics&sprefix=sn74hc165n%2Bshift%2Bregister%2Celectronics%2C153&sr=1-2-catcorr&th=1)

6 x 16 pin IC Sockets <br/>(https://www.amazon.co.uk/16-Pin-DIL-Sockets-Pack/dp/B00KM1O91S/ref=sr_1_2?crid=2ZKVM083D8PRW&keywords=16+pin+chip&qid=1699019985&s=electronics&sprefix=16+pin+chip%2Celectronics%2C119&sr=1-2)

Assorted Male and Female Dupont Header Pins <br/>(https://www.amazon.co.uk/Aussel-6Colors-Breakable-Connector-PIN-6C-60PCS/dp/B078SQ1CZF/ref=sr_1_6?crid=2ITCIHOVTMOAT&keywords=dupont%2Bheader%2Bpins&qid=1699020050&s=electronics&sprefix=dupont%2Bheader%2Bpins%2Celectronics%2C80&sr=1-6&th=1)
16 x 10k Resistors

To drive solenoids, you will need 

4 x DollaTek 4 Channels 4 Route MOSFET Button IRF540 V2.0 for Arduino (https://www.amazon.co.uk/DollaTek-Channels-MOSFET-Button-Arduino/dp/B07MPB52GC/ref=sr_1_15?crid=2H95ZT40UJE51&keywords=mosfet+board&qid=1699020505&sprefix=mosfet+board%2Caps%2C93&sr=8-15)

The code will need customising to your environment

userSettings.h will need updating to meet your wifi environment.  Your ESP32 will need to be quite close to your wireless to work.  I use a cheap netgear wireless extender to achieve this)

switchArray_def.h will need changing to match your plafield.  The first block of code creates instances of the PinballSwitch class.  Think of instance a real thing, with a name and properties of its own.  Each line here we will bring a switch to life so we can work with it.  The parameters in the brackets relate to Switch Name, debounch time in ms, is it a flipper true or false, show debug messages on console yes or no
Later on in the switchArray_def.h we populate an array which is used as an index of switches.  Each row in the array has switch number, a pointer (& PinballSwitch instance name) and then the basic score for the switch.  The Switch number is very important, it must be (the Column number x 8) + the row number on the switch matrix.
Please note, I'm currently breaking the flippers out of the switch matrix so it may appear that flippers can work when part of the switch matrix, but its likely they now wont.

coilArray_def.h is similar to the switchArray_def.h, but this time, the values we need when creating the instances are Name, Output Shift register id, Output Shift register pin, fire time in ms, backoff time in ms.
Later on in the coilArray_def.h we build a coil array.  The coil numbers should be sequencial from 0 up, however have no relevance to physical connections so you can order how you like.

coilBindings_def.h is the file where we define which coils fire as soon as a switch is triggered.  Think Pops and Slings.  The array is should be the same size as the one in switchArray_def.h, the first number in each row refers to a switch id (as per the switchArray_def.h), the second number is 0 for no coil or the number of a coil you want to fire every switch trigger. 

web.h controls the web page elements.  Now there are links in the page that run commands to trigger switches (using AJAX).  You can edit what the links are called in web_dashboard.h.  The actions are at the foot of web.h. 



