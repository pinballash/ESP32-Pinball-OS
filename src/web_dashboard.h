#include <Arduino.h>
const char MAIN_page[] PROGMEM = R"=====(
  <!-- Header -->
  <header class='w3-container' style='padding-top:22px'>
    <h5><b><i class='fa fa-chalkboard-user'></i>Virtual Buttons</b></h5>
  </header>

  <div class='w3-panel'>
    <fieldset id="coilsFieldset">
		  <legend id="formLegend"> Switch Matrix:: </legend>
			<table id="switchTable" style="width:100%;">
				<thead>

				</thead>
				<tbody>
					<tr>
						<th></th>
						<th></th>
						<th></th>
						<th></th>
						<th></th>
						<th></th>
						<th></th>
						<th></th>
						<th></th>
					</tr>
					<tr>
						<th></th>
						<td><span id="0_0" onclick="event_trigger_switch(0,0);"></span></td>
						<td><span id="0_1" onclick="event_trigger_switch(0,1);"></span></td>
						<td><span id="0_2" onclick="event_trigger_switch(0,2);"></span></td>
						<td><span id="0_3" onclick="event_trigger_switch(0,3);"></span></td>
						<td><span id="0_4" onclick="event_trigger_switch(0,4);"></span></td>
						<td><span id="0_5" onclick="event_trigger_switch(0,5);"></span></td>
						<td><span id="0_6" onclick="event_trigger_switch(0,6);"></span></td>
						<td><span id="0_7" onclick="event_trigger_switch(0,7);"></span></td>
					</tr>
					<tr>
						<th></th>
						<td><span id="1_0" onclick="event_trigger_switch(1,0);"></span></td>
						<td><span id="1_1" onclick="event_trigger_switch(1,1);"></span></td>
						<td><span id="1_2" onclick="event_trigger_switch(1,2);"></span></td>
						<td><span id="1_3" onclick="event_trigger_switch(1,3);"></span></td>
						<td><span id="1_4" onclick="event_trigger_switch(1,4);"></span></td>
						<td><span id="1_5" onclick="event_trigger_switch(1,5);"></span></td>
						<td><span id="1_6" onclick="event_trigger_switch(1,6);"></span></td>
						<td><span id="1_7" onclick="event_trigger_switch(1,7);"></span></td>
					</tr>
					<tr>
						<th></th>
						<td><span id="2_0" onclick="event_trigger_switch(2,0);"></span></td>
						<td><span id="2_1" onclick="event_trigger_switch(2,1);"></span></td>
						<td><span id="2_2" onclick="event_trigger_switch(2,2);"></span></td>
						<td><span id="2_3" onclick="event_trigger_switch(2,3);"></span></td>
						<td><span id="2_4" onclick="event_trigger_switch(2,4);"></span></td>
						<td><span id="2_5" onclick="event_trigger_switch(2,5);"></span></td>
						<td><span id="2_6" onclick="event_trigger_switch(2,6);"></span></td>
						<td><span id="2_7" onclick="event_trigger_switch(2,7);"></span></td>
					</tr>
					<tr>
						<th></th>
						<td><span id="3_0" onclick="event_trigger_switch(3,0);"></span></td>
						<td><span id="3_1" onclick="event_trigger_switch(3,1);"></span></td>
						<td><span id="3_2" onclick="event_trigger_switch(3,2);"></span></td>
						<td><span id="3_3" onclick="event_trigger_switch(3,3);"></span></td>
						<td><span id="3_4" onclick="event_trigger_switch(3,4);"></span></td>
						<td><span id="3_5" onclick="event_trigger_switch(3,5);"></span></td>
						<td><span id="3_6" onclick="event_trigger_switch(3,6);"></span></td>
						<td><span id="3_7" onclick="event_trigger_switch(3,7);"></span></td>
					</tr>
					<tr>
						<th></th>
						<td><span id="4_0" onclick="event_trigger_switch(4,0);"></span></td>
						<td><span id="4_1" onclick="event_trigger_switch(4,1);"></span></td>
						<td><span id="4_2" onclick="event_trigger_switch(4,2);"></span></td>
						<td><span id="4_3" onclick="event_trigger_switch(4,3);"></span></td>
						<td><span id="4_4" onclick="event_trigger_switch(4,4);"></span></td>
						<td><span id="4_5" onclick="event_trigger_switch(4,5);"></span></td>
						<td><span id="4_6" onclick="event_trigger_switch(4,6);"></span></td>
						<td><span id="4_7" onclick="event_trigger_switch(4,7);"></span></td>
					</tr>
					<tr>
						<th></th>
						<td><span id="5_0" onclick="event_trigger_switch(5,0);"></span></td>
						<td><span id="5_1" onclick="event_trigger_switch(5,1);"></span></td>
						<td><span id="5_2" onclick="event_trigger_switch(5,2);"></span></td>
						<td><span id="5_3" onclick="event_trigger_switch(5,3);"></span></td>
						<td><span id="5_4" onclick="event_trigger_switch(5,4);"></span></td>
						<td><span id="5_5" onclick="event_trigger_switch(5,5);"></span></td>
						<td><span id="5_6" onclick="event_trigger_switch(5,6);"></span></td>
						<td><span id="5_7" onclick="event_trigger_switch(5,7);"></span></td>
					</tr>
					<tr>
						<th></th>
						<td><span id="6_0" onclick="event_trigger_switch(6,0);"></span></td>
						<td><span id="6_1" onclick="event_trigger_switch(6,1);"></span></td>
						<td><span id="6_2" onclick="event_trigger_switch(6,2);"></span></td>
						<td><span id="6_3" onclick="event_trigger_switch(6,3);"></span></td>
						<td><span id="6_4" onclick="event_trigger_switch(6,4);"></span></td>
						<td><span id="6_5" onclick="event_trigger_switch(6,5);"></span></td>
						<td><span id="6_6" onclick="event_trigger_switch(6,6);"></span></td>
						<td><span id="6_7" onclick="event_trigger_switch(6,7);"></span></td>
					</tr>
					<tr>
						<th></th>
						<td><span id="7_0" onclick="event_trigger_switch(7,0);"></span></td>
						<td><span id="7_1" onclick="event_trigger_switch(7,1);"></span></td>
						<td><span id="7_2" onclick="event_trigger_switch(7,2);"></span></td>
						<td><span id="7_3" onclick="event_trigger_switch(7,3);"></span></td>
						<td><span id="7_4" onclick="event_trigger_switch(7,4);"></span></td>
						<td><span id="7_5" onclick="event_trigger_switch(7,5);"></span></td>
						<td><span id="7_6" onclick="event_trigger_switch(7,6);"></span></td>
						<td><span id="7_7" onclick="event_trigger_switch(7,7);"></span></td>
					</tr>
				</tbody>
				<tfoot>
					
				</tfoot>
			</table>
		</fieldset>
  </div>




  <div class='w3-panel'>
    <div class='w3-row-padding' style='margin:0 -16px'>
      <div class='w3-third'>
        <h5>Machine State</h5>
        <div class='w3-container w3-orange w3-text-white w3-padding-16'>
            <div class='w3-left'><i class='fa fa-gamepad w3-xxxlarge'></i></div>
            <div class='w3-right'>
              <h3><span id='machineState'>Not Read Yet</span></h3>
            </div>
            <div class='w3-clear'></div>
            <h4>Machine State</h4>
          </div>
      </div>
      <div class='w3-twothird'>
        <h5>Stats</h5>
        <table class='w3-table w3-striped w3-bordered w3-border w3-hoverable w3-white'>
          <tr>
            <td><i class='fa fa-microchip w3-text-blue w3-large'></i></td>
            <td>Core Machine Operations</td>
            <td><i><span id='cpu0Hz'>Not Read Yet</span></i></td>
          </tr>
          <tr>
            <td><i class='fa fa-microchip w3-text-red w3-large'></i></td>
            <td>Webserver Operations</td>
            <td><i><span id='cpu1Hz'>Not Read Yet</span></i></td>
          </tr>
          <tr>
            <td><i class='fa fa-user w3-text-red w3-large'></i></td>
            <td>Current Player</td>
            <td><i><span id='playerNumber'>Not Read Yet</span></i></td>
          </tr>
          <tr>
            <td><i class='fa fa-bullseye w3-text-red w3-large'></i></td>
            <td>Ball Number</td>
            <td><i><span id='ballNumber'>Not Read Yet</span></i></td>
          </tr>
          <tr>
            <td><i class='fa fa-bookmark w3-text-red w3-large'></i></td>
            <td>Player Score</td>
            <td><i><span id='playerScore'>Not Read Yet</span></i></td>
          </tr>    
          <tr>
            <td><i class='fa fa-suitcase medical w3-text-red w3-large'></i></td>
            <td>Ball Save Active</td>
            <td><i><span id='ballSave'>Not Read Yet</span></i></td>
          </tr>       
        </table>
      </div>
    </div>
  </div>
  <hr>
  <header class='w3-container w3-blue-grey w3-center'>
    <h2 class='w3-monospace w3-text-red'><span id='topDisplay'></span></h2>
  </header>
    <header class='w3-container w3-blue-grey w3-center'>
    <h2 class='w3-monospace w3-text-red'><span id='bottomDisplay'></span></h2>
  </header>


  <div class='w3-container'>
    <h5>Player Stats</h5>
    <table class='w3-table w3-striped w3-bordered w3-border w3-hoverable w3-white'>
      <tr>  
        <th>No.</th>
        <th>Score</th>
        <th>Ball</th>
      <tr>
        <td>1</td>
        <td><span id='p1score'>0</span></td>
        <td><span id='p1ball'>0</span></td>
      </tr>
      <tr>
        <td>2</td>
        <td><span id='p2score'>0</span></td>
        <td><span id='p2ball'>0</span></td>
      </tr>
      <tr>
        <td>3</td>
        <td><span id='p3score'>0</span></td>
        <td><span id='p3ball'>0</span></td>
      </tr>
      <tr>
        <td>4</td>
        <td><span id='p4score'>0</span></td>
        <td><span id='p4ball'>0</span></td>
      </tr>
    </table>
  </div>
  <div class='w3-container'>
    <h5>Top Scores</h5>
    <table class='w3-table w3-striped w3-bordered w3-border w3-hoverable w3-white'>
      <tr>
        <td>ASH</td>
        <td>1,000,000</td>
      </tr>
      <tr>
        <td>ASH</td>
        <td>900,000</td>
      </tr>
      <tr>
        <td>ASH</td>
        <td>800,000</td>
      </tr>
      <tr>
        <td>ASH</td>
        <td>700,000</td>
      </tr>
      <tr>
        <td>ASH</td>
        <td>600,000</td>
      </tr>
      <tr>
        <td>ASH</td>
        <td>500,000</td>
      </tr>
      <tr>
        <td>ASH</td>
        <td>450,000</td>
      </tr>
      <tr>
        <td>ASH</td>
        <td>400,000</td>
      </tr>
      <tr>
        <td>ASH</td>
        <td>350,000</td>
      </tr>
      <tr>
        <td>ASH</td>
        <td>300,000</td>
      </tr>
      
    </table>
  </div>
 <hr>
     <header class='w3-container w3-blue-grey w3-center'>
    <h2>Console Debug Switches</h2>
  </header>   
 <div class='w3-row-padding w3-margin-bottom'>
    <!-- button start-->
    <div class='w3-quarter'>
      <div class='w3-container w3-green w3-padding-16'>
          <button onclick='event_debugSwitch_click();' class='w3-button w3-green'>Debug Switches</button>
      </div>
    </div>
    
 
    <!-- button start-->
    <div class='w3-quarter'>
        <div class='w3-container w3-red w3-padding-16'>
            <button onclick='event_debugCoil_click();' class='w3-button w3-red'>Debug Coils</button>
        </div>
    </div>
    
 
    <!-- button start-->
    <div class='w3-quarter'>
        <div class='w3-container w3-red w3-padding-16'>
            <button onclick='event_debugOps_click();' class='w3-button w3-red'>Debug Ops</button>
        </div>
    </div>
  </div>
)=====";