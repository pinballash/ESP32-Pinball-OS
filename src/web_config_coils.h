#include <Arduino.h>
const char CONFIG_COILS_page[] PROGMEM = R"=====(
    <!-- Header -->
  <header class='w3-container' style='padding-top:22px'>
    <h5><b><i class='fa fa-chalkboard-user'></i>Switch Configuration</b></h5>
  </header>
  <div>
	<code>
	<span id='config'></span>
	</code>
  </div>
  <div>
	
		<fieldset id="coilsFieldset">
		  <legend id="formLegend"> Coils:: </legend>

			<table id="switchTable" style="width:100%;">
				
				<thead>
					<tr>
						<th>Rows</th>
						<th colspan="3">OSR</th>
					</tr>

				</thead>
				<tbody>
					<tr>
						<th></th>
						<th>0</th>
						<th>1</th>
					</tr>
					<tr>
						<th>0</th>
						<td><span id="0_0" onclick="selectCoil(0,0);"></span></td>
						<td><span id="0_1" onclick="selectCoil(0,1);"></span></td>
					</tr>
					<tr>
						<th>1</th>
						<td><span id="1_0" onclick="selectCoil(1,0);"></span></td>
						<td><span id="1_1" onclick="selectCoil(1,1);"></span></td>
					</tr>
					<tr>
						<th>2</th>
						<td><span id="2_0" onclick="selectCoil(2,0);"></span></td>
						<td><span id="2_1" onclick="selectCoil(2,1);"></span></td>
					</tr>
					<tr>
						<th>3</th>
						<td><span id="3_0" onclick="selectCoil(3,0);"></span></td>
						<td><span id="3_1" onclick="selectCoil(3,1);"></span></td>
					</tr>
					<tr>
						<th>4</th>
						<td><span id="4_0" onclick="selectCoil(4,0);"></span></td>
						<td><span id="4_1" onclick="selectCoil(4,1);"></span></td>
					</tr>
					<tr>
						<th>5</th>
						<td><span id="5_0" onclick="selectCoil(5,0);"></span></td>
						<td><span id="5_1" onclick="selectCoil(5,1);"></span></td>
					</tr>
					<tr>
						<th>6</th>
						<td><span id="6_0" onclick="selectCoil(6,0);"></span></td>
						<td><span id="6_1" onclick="selectCoil(6,1);"></span></td>
					</tr>
					<tr>
						<th>7</th>
						<td><span id="7_0" onclick="selectCoil(7,0);"></span></td>
						<td><span id="7_1" onclick="selectCoil(7,1);"></span></td>
					</tr>
				</tbody>
				<tfoot>
					
				</tfoot>
			</table>

		</fieldset>


	
	<div id="CoilEdit" style="display:none;">
		<form id="configForm" name="configForm" class="configForm"  method="POST" action="#" enctype="multipart/form-data" target="_self">
		<fieldset id="coilsFieldset">
		  <legend id="formLegend"> Coil Edit:: </legend>
			<!--String coilName, byte shiftRegister, byte shiftRegisterBit, int pulseTime, int pulseBackOff -->
			<table id="coilEditTable">
				<thead>
					<tr>
						<th>Element</th>
						<th>Setting Value</th>
					</tr>
					
				</thead>
				<tbody>
					<tr>
						<td><label for="coilId">Coil ID</label></td>
						<td><input type="text" id="coilId" value="-1"></td>
					</tr>
					<tr>
						<td><label for="coilName">Coil Name</label></td>
						<td><input type="text" id="coilName" value=""></td>
					</tr>
					<tr>
						<td><label for="shiftRegister">Shift Register</label></td>
						<td><input type="text" id="shiftRegister" value=""></td>
					</tr>
					<tr>
						<td><label for="shiftRegisterBit">Shift Register Bit</label></td>
						<td><input type="text" id="shiftRegisterBit" value=""></td>
					</tr>
					<tr>
						<td><label for="pulseTime">Pulse Time (ms)</label></td>
						<td><input type="text" id="pulseTime" value=""></td>
					</tr>
					<tr>
						<td><label for="pulseBackOff">Pulse Back Off Time (ms)</label></td>
						<td><input type="text" id="pulseBackOff" value=""></td>
					</tr>
				</tbody>
				<tfoot>
				</tfoot>
			</table>	

		</fieldset>
		<input type="button" id="submitButton" value="Submit">
	</form>
	</div>

  </div>
  <!-- Footer -->
  <footer class='w3-container w3-padding-16 w3-light-grey'>
    <!--<h4>FOOTER</h4>-->
    <!--<p>Powered by <a href='https://www.w3schools.com/w3css/default.asp' target='_blank'>w3.css</a></p>-->
  </footer>

  <!-- End page content -->
</div>


)=====";