#include <Arduino.h>
const char MAIN_page[] PROGMEM = R"=====(
  <!-- Header -->
  <header class='w3-container' style='padding-top:22px'>
    <h5><b><i class='fa fa-chalkboard-user'></i>Virtual Buttons</b></h5>
  </header>
  <!-- button row 1 -->
  <div class='w3-row-padding w3-margin-bottom'>
      <!-- button start-->
      <div class='w3-quarter'>
        <div class='w3-container w3-green w3-padding-16'>
          <div class='w3-left'><i class='fa fa-play w3-xxlarge'></i></div>
              <button onclick='event_start_click();' class='w3-button w3-green'>Press Start</button>
        </div>
      </div>
    
 
    <!-- button start-->
      <div class='w3-quarter'>
          <div class='w3-container w3-red w3-padding-16'>
              <div class='w3-left'><i class='fa fa-power-off w3-xxlarge'></i></div>
                  <button onclick='event_restart_click();' class='w3-button w3-red'>Restart</button>
          </div>
      </div>
    </div>
    <!-- button row 2 -->
    <div class='w3-row-padding w3-margin-bottom'>
                <button onclick='event_leftrolloverswitch_click();' class='w3-button w3-border'>Left Rollover</button>
                <button onclick='event_leftrolloverswitch_click();' class='w3-button w3-border'> Center Rollover</button>
                <button onclick='event_rightrolloverswitch_click();' class='w3-button w3-border'>Right Rollover</button>
                <button onclick='event_saucerswitch_click();' class='w3-button w3-border'>Saucer</button>
    </div>
    <!-- button row 3 -->
    <div class='w3-row-padding w3-margin-bottom'>
                <button onclick='event_lefttoplaneswitch_click();' class='w3-button w3-border'>Left Toplane</button>
                <button onclick='event_centertoplaneswitch_click();' class='w3-button w3-border'>Center Toplane</button> 
                <button onclick='event_righttoplaneswitch_click();' class='w3-button w3-border'>Right Toplane</button>
    </div>
    <!-- button row 4 -->
    <div class='w3-row-padding w3-margin-bottom'>
                <button onclick='event_spinnerswitch_click();' class='w3-button w3-border'>Spinner</button>
                <button onclick='event_leftpopswitch_click();' class='w3-button w3-border'>Left Pop</button>
                <button onclick='event_rightpopswitch_click();' class='w3-button w3-border'>Right Pop</button>
  </div>
  <!-- button row 5 -->
  <div class='w3-row-padding w3-margin-bottom'>
               <button onclick='event_drop1switch_click();' class='w3-button w3-border'>Drop 1</button>
                <button onclick='event_drop2switch_click();' class='w3-button w3-border'>Drop 2</button>
                <button onclick='event_drop3switch_click();' class='w3-button w3-border'>Drop 3</button>   
                <button onclick='event_drop4switch_click();' class='w3-button w3-border'>Drop 4</button>
                <button onclick='event_drop5switch_click();' class='w3-button w3-border'>Drop 5</button>
              
  </div>
  <!-- button row 6 -->
  <div class='w3-row-padding w3-margin-bottom'>
              <button onclick='event_standup1switch_click();' class='w3-button w3-border'>Standup 1</button>
              <button onclick='event_standup2switch_click();' class='w3-button w3-border'>Standup 2</button>
              <button onclick='event_standup3switch_click();' class='w3-button w3-border'>Standup 3</button>
              <button onclick='event_standup4switch_click();' class='w3-button w3-border'>Standup 4</button>
              <button onclick='event_standup5switch_click();' class='w3-button w3-border'>Standup 5</button>
                
  </div>
  <!-- button row 7 -->
  <div class='w3-row-padding w3-margin-bottom'>
                 <button onclick='event_leftoutlaneswitch_click();' class='w3-button w3-border'>Left Outlane</button>
                <button onclick='event_leftinlaneswitch_click();' class='w3-button w3-border'>Left Inlane</button>
                <button onclick='event_outhole_click();' class='w3-button w3-red'>Outhole</button>
                <button onclick='event_rightinlaneswitch_click();' class='w3-button w3-border'>Right Inlane</button>
                <button onclick='event_rightoutlaneswitch_click();' class='w3-button w3-border'>Right Outlane</button>
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