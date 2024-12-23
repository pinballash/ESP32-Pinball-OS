#include <Arduino.h>
const char CONFIG_SWITCHES_SCORES_page[] PROGMEM = R"=====(
    <!-- Header -->
  <header class='w3-container' style='padding-top:22px'>
    <h5><b><i class='fa fa-chalkboard-user'></i>Score Configuration</b></h5>
  </header>
  <div>
	<code>
	<span id='config'></span>
	</code>
  </div>
  <div>
	
		<fieldset id="coilsFieldset">
		  <legend id="formLegend"> Switch Matrix:: </legend>

			<table id="switchTable" style="width:100%;">
				
				<thead>
					<tr>
						<th>Rows</th>
						<th colspan="9">Columns</th>
					</tr>

				</thead>
				<tbody>
					<tr>
						<th></th>
						<th>0</th>
						<th>1</th>
						<th>2</th>
						<th>3</th>
						<th>4</th>
						<th>5</th>
						<th>6</th>
						<th>7</th>
					</tr>
					<tr>
						<th>0</th>
						<td><span id="0_0" onclick="selectSwitch(0,0);"></span></td>
						<td><span id="0_1" onclick="selectSwitch(0,1);"></span></td>
						<td><span id="0_2" onclick="selectSwitch(0,2);"></span></td>
						<td><span id="0_3" onclick="selectSwitch(0,3);"></span></td>
						<td><span id="0_4" onclick="selectSwitch(0,4);"></span></td>
						<td><span id="0_5" onclick="selectSwitch(0,5);"></span></td>
						<td><span id="0_6" onclick="selectSwitch(0,6);"></span></td>
						<td><span id="0_7" onclick="selectSwitch(0,7);"></span></td>
				
					</tr>
					<tr>
						<th>1</th>
						<td><span id="1_0" onclick="selectSwitch(1,0);"></span></td>
						<td><span id="1_1" onclick="selectSwitch(1,1);"></span></td>
						<td><span id="1_2" onclick="selectSwitch(1,2);"></span></td>
						<td><span id="1_3" onclick="selectSwitch(1,3);"></span></td>
						<td><span id="1_4" onclick="selectSwitch(1,4);"></span></td>
						<td><span id="1_5" onclick="selectSwitch(1,5);"></span></td>
						<td><span id="1_6" onclick="selectSwitch(1,6);"></span></td>
						<td><span id="1_7" onclick="selectSwitch(1,7);"></span></td>
				
					</tr>
					<tr>
						<th>2</th>
						<td><span id="2_0" onclick="selectSwitch(2,0);"></span></td>
						<td><span id="2_1" onclick="selectSwitch(2,1);"></span></td>
						<td><span id="2_2" onclick="selectSwitch(2,2);"></span></td>
						<td><span id="2_3" onclick="selectSwitch(2,3);"></span></td>
						<td><span id="2_4" onclick="selectSwitch(2,4);"></span></td>
						<td><span id="2_5" onclick="selectSwitch(2,5);"></span></td>
						<td><span id="2_6" onclick="selectSwitch(2,6);"></span></td>
						<td><span id="2_7" onclick="selectSwitch(2,7);"></span></td>

					
					</tr>
					<tr>
						<th>3</th>
						<td><span id="3_0" onclick="selectSwitch(3,0);"></span></td>
						<td><span id="3_1" onclick="selectSwitch(3,1);"></span></td>
						<td><span id="3_2" onclick="selectSwitch(3,2);"></span></td>
						<td><span id="3_3" onclick="selectSwitch(3,3);"></span></td>
						<td><span id="3_4" onclick="selectSwitch(3,4);"></span></td>
						<td><span id="3_5" onclick="selectSwitch(3,5);"></span></td>
						<td><span id="3_6" onclick="selectSwitch(3,6);"></span></td>
						<td><span id="3_7" onclick="selectSwitch(3,7);"></span></td>
						
					</tr>
					<tr>
						<th>4</th>
						<td><span id="4_0" onclick="selectSwitch(4,0);"></span></td>
						<td><span id="4_1" onclick="selectSwitch(4,1);"></span></td>
						<td><span id="4_2" onclick="selectSwitch(4,2);"></span></td>
						<td><span id="4_3" onclick="selectSwitch(4,3);"></span></td>
						<td><span id="4_4" onclick="selectSwitch(4,4);"></span></td>
						<td><span id="4_5" onclick="selectSwitch(4,5);"></span></td>
						<td><span id="4_6" onclick="selectSwitch(4,6);"></span></td>
						<td><span id="4_7" onclick="selectSwitch(4,7);"></span></td>
											
					</tr>
					<tr>
						<th>5</th>
						<td><span id="5_0" onclick="selectSwitch(5,0);"></span></td>
						<td><span id="5_1" onclick="selectSwitch(5,1);"></span></td>
						<td><span id="5_2" onclick="selectSwitch(5,2);"></span></td>
						<td><span id="5_3" onclick="selectSwitch(5,3);"></span></td>
						<td><span id="5_4" onclick="selectSwitch(5,4);"></span></td>
						<td><span id="5_5" onclick="selectSwitch(5,5);"></span></td>
						<td><span id="5_6" onclick="selectSwitch(5,6);"></span></td>
						<td><span id="5_7" onclick="selectSwitch(5,7);"></span></td>
					
					</tr>
					<tr>
						<th>6</th>
						<td><span id="6_0" onclick="selectSwitch(6,0);"></span></td>
						<td><span id="6_1" onclick="selectSwitch(6,1);"></span></td>
						<td><span id="6_2" onclick="selectSwitch(6,2);"></span></td>
						<td><span id="6_3" onclick="selectSwitch(6,3);"></span></td>
						<td><span id="6_4" onclick="selectSwitch(6,4);"></span></td>
						<td><span id="6_5" onclick="selectSwitch(6,5);"></span></td>
						<td><span id="6_6" onclick="selectSwitch(6,6);"></span></td>
						<td><span id="6_7" onclick="selectSwitch(6,7);"></span></td>
					
					</tr>
					<tr>
						<th>7</th>
						<td><span id="7_0" onclick="selectSwitch(7,0);"></span></td>
						<td><span id="7_1" onclick="selectSwitch(7,1);"></span></td>
						<td><span id="7_2" onclick="selectSwitch(7,2);"></span></td>
						<td><span id="7_3" onclick="selectSwitch(7,3);"></span></td>
						<td><span id="7_4" onclick="selectSwitch(7,4);"></span></td>
						<td><span id="7_5" onclick="selectSwitch(7,5);"></span></td>
						<td><span id="7_6" onclick="selectSwitch(7,6);"></span></td>
						<td><span id="7_7" onclick="selectSwitch(7,7);"></span></td>
							
					</tr>

					
				</tbody>
				<tfoot>
					
				</tfoot>
			</table>

		</fieldset>


	
	<div id="SwitchEdit" style="display:none;">
		<form id="configForm" name="configForm" class="configForm"  method="POST" action="#" enctype="multipart/form-data" target="_self">
		<fieldset id="coilsFieldset">
		  <legend id="formLegend"> Switch Score Edit:: </legend>
			<!--Name, Debouce, isFlipper,debug -->
			<table id="switchEditTable">
				<thead>
					<tr>
						<th>Element</th>
						<th>Setting Value</th>
					</tr>
					
				</thead>
				<tbody>
					<tr>
						<td><label for="switchId">Switch ID</label></td>
						<td><input type="text" id="switchId" value="-1" readonly></td>
					</tr>
					<tr>
						<td><label for="switchName">Switch Name</label></td>
						<td><input type="text" id="switchName" value="" readonly></td>
					</tr>
					<tr>
						<td><label for="switchScore">Score</label></td>
						<td><input type="text" id="switchScore" value=""></td>
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