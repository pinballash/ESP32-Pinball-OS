#include <Arduino.h>
const char CONFIG_LEDS_page[] PROGMEM = R"=====(
<!-- Header -->
  <header class='w3-container' style='padding-top:22px'>
    <h5><b><i class='fa fa-chalkboard-user'></i>LED Configuration</b></h5>
  </header>
  <div>
	<code>
	<span id='config'></span>
	</code>
  </div>
  <div>	
		<fieldset id="ledFieldset">
		  <legend id="formLegend">WS2812 LED Sting:: </legend>
		  <input type="button" id="LoadLEDsButton" value="Load">
			<table id="ledTable" style="width:100%;">	
				<thead>
				</thead>
				<tbody>	
					<tr>
						<td><span id="0_0" onclick="selectLED(0,0);">0</span></td>
						<td><span id="0_1" onclick="selectLED(0,1);">1</span></td>
						<td><span id="0_2" onclick="selectLED(0,2);">2</span></td>
						<td><span id="0_3" onclick="selectLED(0,3);">3</span></td>
						<td><span id="0_4" onclick="selectLED(0,4);">4</span></td>
						<td><span id="0_5" onclick="selectLED(0,5);">5</span></td>
						<td><span id="0_6" onclick="selectLED(0,6);">6</span></td>
						<td><span id="0_7" onclick="selectLED(0,7);">7</span></td>
                        <td><span id="0_8" onclick="selectLED(0,8);">8</span></td>
						<td><span id="0_9" onclick="selectLED(0,9);">9</span></td>
						<td><span id="0_10" onclick="selectLED(0,10);">10</span></td>
						<td><span id="0_11" onclick="selectLED(0,11);">11</span></td>
						<td><span id="0_12" onclick="selectLED(0,12);">12</span></td>
						<td><span id="0_13" onclick="selectLED(0,13);">13</span></td>
						<td><span id="0_14" onclick="selectLED(0,14);">14</span></td>
						<td><span id="0_15" onclick="selectLED(0,15);">15</span></td>
					</tr>
					<tr>
						<td><span id="1_0" onclick="selectLED(1,0);">16</span></td>
						<td><span id="1_1" onclick="selectLED(1,1);">17</span></td>
						<td><span id="1_2" onclick="selectLED(1,2);">18</span></td>
						<td><span id="1_3" onclick="selectLED(1,3);">19</span></td>
						<td><span id="1_4" onclick="selectLED(1,4);">20</span></td>
						<td><span id="1_5" onclick="selectLED(1,5);">21</span></td>
						<td><span id="1_6" onclick="selectLED(1,6);">22</span></td>
						<td><span id="1_7" onclick="selectLED(1,7);">23</span></td>
                        <td><span id="1_8" onclick="selectLED(1,8);">24</span></td>
						<td><span id="1_9" onclick="selectLED(1,9);">25</span></td>
						<td><span id="1_10" onclick="selectLED(1,10);">26</span></td>
						<td><span id="1_11" onclick="selectLED(1,11);">27</span></td>
						<td><span id="1_12" onclick="selectLED(1,12);">28</span></td>
						<td><span id="1_13" onclick="selectLED(1,13);">29</span></td>
						<td><span id="1_14" onclick="selectLED(1,14);">30</span></td>
						<td><span id="1_15" onclick="selectLED(1,15);">31</span></td>
					</tr>
					<tr>
						<td><span id="2_0" onclick="selectLED(2,0);">32</span></td>
						<td><span id="2_1" onclick="selectLED(2,1);">33</span></td>
						<td><span id="2_2" onclick="selectLED(2,2);">34</span></td>
						<td><span id="2_3" onclick="selectLED(2,3);">35</span></td>
						<td><span id="2_4" onclick="selectLED(2,4);">36</span></td>
						<td><span id="2_5" onclick="selectLED(2,5);">37</span></td>
						<td><span id="2_6" onclick="selectLED(2,6);">38</span></td>
						<td><span id="2_7" onclick="selectLED(2,7);">39</span></td>
                        <td><span id="2_8" onclick="selectLED(2,8);">40</span></td>
						<td><span id="2_9" onclick="selectLED(2,9);">41</span></td>
						<td><span id="2_10" onclick="selectLED(2,10);">42</span></td>
						<td><span id="2_11" onclick="selectLED(2,11);">43</span></td>
						<td><span id="2_12" onclick="selectLED(2,12);">44</span></td>
						<td><span id="2_13" onclick="selectLED(2,13);">45</span></td>
						<td><span id="2_14" onclick="selectLED(2,14);">46</span></td>
						<td><span id="2_15" onclick="selectLED(2,15);">47</span></td>				
					</tr>
					<tr>
						<td><span id="3_0" onclick="selectLED(3,0);">48</span></td>
						<td><span id="3_1" onclick="selectLED(3,1);">49</span></td>
						<td><span id="3_2" onclick="selectLED(3,2);">50</span></td>
						<td><span id="3_3" onclick="selectLED(3,3);">51</span></td>
						<td><span id="3_4" onclick="selectLED(3,4);">52</span></td>
						<td><span id="3_5" onclick="selectLED(3,5);">53</span></td>
						<td><span id="3_6" onclick="selectLED(3,6);">54</span></td>
						<td><span id="3_7" onclick="selectLED(3,7);">55</span></td>
                        <td><span id="3_8" onclick="selectLED(3,8);">56</span></td>
						<td><span id="3_9" onclick="selectLED(3,9);">57</span></td>
						<td><span id="3_10" onclick="selectLED(3,10);">58</span></td>
						<td><span id="3_11" onclick="selectLED(3,11);">59</span></td>
						<td><span id="3_12" onclick="selectLED(3,12);">60</span></td>
						<td><span id="3_13" onclick="selectLED(3,13);">61</span></td>
						<td><span id="3_14" onclick="selectLED(3,14);">62</span></td>
						<td><span id="3_15" onclick="selectLED(3,15);">63</span></td>
					</tr>
					<tr>
						<td><span id="4_0" onclick="selectLED(4,0);">64</span></td>
						<td><span id="4_1" onclick="selectLED(4,1);">65</span></td>
						<td><span id="4_2" onclick="selectLED(4,2);">66</span></td>
						<td><span id="4_3" onclick="selectLED(4,3);">67</span></td>
						<td><span id="4_4" onclick="selectLED(4,4);">68</span></td>
						<td><span id="4_5" onclick="selectLED(4,5);">69</span></td>
						<td><span id="4_6" onclick="selectLED(4,6);">70</span></td>
						<td><span id="4_7" onclick="selectLED(4,7);">71</span></td>
                        <td><span id="4_8" onclick="selectLED(4,8);">72</span></td>
						<td><span id="4_9" onclick="selectLED(4,9);">73</span></td>
						<td><span id="4_10" onclick="selectLED(4,10);">74</span></td>
						<td><span id="4_11" onclick="selectLED(4,11);">75</span></td>
						<td><span id="4_12" onclick="selectLED(4,12);">76</span></td>
						<td><span id="4_13" onclick="selectLED(4,13);">77</span></td>
						<td><span id="4_14" onclick="selectLED(4,14);">78</span></td>
						<td><span id="4_15" onclick="selectLED(4,15);">79</span></td>
					</tr>
					<tr>
						<td><span id="5_0" onclick="selectLED(5,0);">80</span></td>
						<td><span id="5_1" onclick="selectLED(5,1);">81</span></td>
						<td><span id="5_2" onclick="selectLED(5,2);">82</span></td>
						<td><span id="5_3" onclick="selectLED(5,3);">83</span></td>
						<td><span id="5_4" onclick="selectLED(5,4);">84</span></td>
						<td><span id="5_5" onclick="selectLED(5,5);">85</span></td>
						<td><span id="5_6" onclick="selectLED(5,6);">86</span></td>
						<td><span id="5_7" onclick="selectLED(5,7);">87</span></td>
                        <td><span id="5_8" onclick="selectLED(5,8);">88</span></td>
						<td><span id="5_9" onclick="selectLED(5,9);">89</span></td>
						<td><span id="5_10" onclick="selectLED(5,10);">90</span></td>
						<td><span id="5_11" onclick="selectLED(5,11);">91</span></td>
						<td><span id="5_12" onclick="selectLED(5,12);">92</span></td>
						<td><span id="5_13" onclick="selectLED(5,13);">93</span></td>
						<td><span id="5_14" onclick="selectLED(5,14);">94</span></td>
						<td><span id="5_15" onclick="selectLED(5,15);">95</span></td>
					</tr>
					<tr>
						<td><span id="6_0" onclick="selectLED(6,0);">96</span></td>
						<td><span id="6_1" onclick="selectLED(6,1);">97</span></td>
						<td><span id="6_2" onclick="selectLED(6,2);">98</span></td>
						<td><span id="6_3" onclick="selectLED(6,3);">99</span></td>
						<td><span id="6_4" onclick="selectLED(6,4);">100</span></td>
						<td><span id="6_5" onclick="selectLED(6,5);">101</span></td>
						<td><span id="6_6" onclick="selectLED(6,6);">102</span></td>
						<td><span id="6_7" onclick="selectLED(6,7);">103</span></td>
                        <td><span id="6_8" onclick="selectLED(6,8);">104</span></td>
						<td><span id="6_9" onclick="selectLED(6,9);">105</span></td>
						<td><span id="6_10" onclick="selectLED(6,10);">106</span></td>
						<td><span id="6_11" onclick="selectLED(6,11);">107</span></td>
						<td><span id="6_12" onclick="selectLED(6,12);">108</span></td>
						<td><span id="6_13" onclick="selectLED(6,13);">109</span></td>
						<td><span id="6_14" onclick="selectLED(6,14);">110</span></td>
						<td><span id="6_15" onclick="selectLED(6,15);">111</span></td>					
					</tr>
					<tr>	
						<td><span id="7_0" onclick="selectLED(7,0);">112</span></td>
						<td><span id="7_1" onclick="selectLED(7,1);">113</span></td>
						<td><span id="7_2" onclick="selectLED(7,2);">114</span></td>
						<td><span id="7_3" onclick="selectLED(7,3);">115</span></td>
						<td><span id="7_4" onclick="selectLED(7,4);">116</span></td>
						<td><span id="7_5" onclick="selectLED(7,5);">117</span></td>
						<td><span id="7_6" onclick="selectLED(7,6);">118</span></td>
						<td><span id="7_7" onclick="selectLED(7,7);">119</span></td>
                        <td><span id="7_8" onclick="selectLED(7,8);">120</span></td>
						<td><span id="7_9" onclick="selectLED(7,9);">121</span></td>
						<td><span id="7_10" onclick="selectLED(7,10);">122</span></td>
						<td><span id="7_11" onclick="selectLED(7,11);">123</span></td>
						<td><span id="7_12" onclick="selectLED(7,12);">124</span></td>
						<td><span id="7_13" onclick="selectLED(7,13);">125</span></td>
						<td><span id="7_14" onclick="selectLED(7,14);">126</span></td>
						<td><span id="7_15" onclick="selectLED(7,15);">127</span></td>
					</tr>
                    <tr>
						<td><span id="8_0" onclick="selectLED(8,0);">128</span></td>
						<td><span id="8_1" onclick="selectLED(8,1);">129</span></td>
						<td><span id="8_2" onclick="selectLED(8,2);">130</span></td>
						<td><span id="8_3" onclick="selectLED(8,3);">131</span></td>
						<td><span id="8_4" onclick="selectLED(8,4);">132</span></td>
						<td><span id="8_5" onclick="selectLED(8,5);">133</span></td>
						<td><span id="8_6" onclick="selectLED(8,6);">134</span></td>
						<td><span id="8_7" onclick="selectLED(8,7);">135</span></td>
                        <td><span id="8_8" onclick="selectLED(8,8);">136</span></td>
						<td><span id="8_9" onclick="selectLED(8,9);">137</span></td>
						<td><span id="8_10" onclick="selectLED(8,10);">138</span></td>
						<td><span id="8_11" onclick="selectLED(8,11);">139</span></td>
						<td><span id="8_12" onclick="selectLED(8,12);">140</span></td>
						<td><span id="8_13" onclick="selectLED(8,13);">141</span></td>
						<td><span id="8_14" onclick="selectLED(8,14);">142</span></td>
						<td><span id="8_15" onclick="selectLED(8,15);">143</span></td>
                    </tr>
                    <tr>
						<td><span id="9_0" onclick="selectLED(9,0);">144</span></td>
						<td><span id="9_1" onclick="selectLED(9,1);">145</span></td>
						<td><span id="9_2" onclick="selectLED(9,2);">146</span></td>
						<td><span id="9_3" onclick="selectLED(9,3);">147</span></td>
						<td><span id="9_4" onclick="selectLED(9,4);">148</span></td>
						<td><span id="9_5" onclick="selectLED(9,5);">149</span></td>
						<td><span id="9_6" onclick="selectLED(9,6);">150</span></td>
						<td><span id="9_7" onclick="selectLED(9,7);">151</span></td>
                        <td><span id="9_8" onclick="selectLED(9,8);">152</span></td>
						<td><span id="9_9" onclick="selectLED(9,9);">153</span></td>
						<td><span id="9_10" onclick="selectLED(9,10);">154</span></td>
						<td><span id="9_11" onclick="selectLED(9,11);">155</span></td>
						<td><span id="9_12" onclick="selectLED(9,12);">156</span></td>
						<td><span id="9_13" onclick="selectLED(9,13);">157</span></td>
						<td><span id="9_14" onclick="selectLED(9,14);">158</span></td>
						<td><span id="9_15" onclick="selectLED(9,15);">159</span></td>
                    </tr>
                    <tr>
						<td><span id="10_0" onclick="selectLED(10,0);">160</span></td>
						<td><span id="10_1" onclick="selectLED(10,1);">161</span></td>
						<td><span id="10_2" onclick="selectLED(10,2);">162</span></td>
						<td><span id="10_3" onclick="selectLED(10,3);">163</span></td>
						<td><span id="10_4" onclick="selectLED(10,4);">164</span></td>
						<td><span id="10_5" onclick="selectLED(10,5);">165</span></td>
						<td><span id="10_6" onclick="selectLED(10,6);">166</span></td>
						<td><span id="10_7" onclick="selectLED(10,7);">167</span></td>
                        <td><span id="10_8" onclick="selectLED(10,8);">168</span></td>
						<td><span id="10_9" onclick="selectLED(10,9);">169</span></td>
						<td><span id="10_10" onclick="selectLED(10,10);">170</span></td>
						<td><span id="10_11" onclick="selectLED(10,11);">171</span></td>
						<td><span id="10_12" onclick="selectLED(10,12);">172</span></td>
						<td><span id="10_13" onclick="selectLED(10,13);">173</span></td>
						<td><span id="10_14" onclick="selectLED(10,14);">174</span></td>
						<td><span id="10_15" onclick="selectLED(10,15);">175</span></td>
                    </tr>
                    <tr>
						<td><span id="11_0" onclick="selectLED(11,0);">176</span></td>
						<td><span id="11_1" onclick="selectLED(11,1);">177</span></td>
						<td><span id="11_2" onclick="selectLED(11,2);">178</span></td>
						<td><span id="11_3" onclick="selectLED(11,3);">179</span></td>
						<td><span id="11_4" onclick="selectLED(11,4);">180</span></td>
						<td><span id="11_5" onclick="selectLED(11,5);">181</span></td>
						<td><span id="11_6" onclick="selectLED(11,6);">182</span></td>
						<td><span id="11_7" onclick="selectLED(11,7);">183</span></td>
                        <td><span id="11_8" onclick="selectLED(11,8);">184</span></td>
						<td><span id="11_9" onclick="selectLED(11,9);">185</span></td>
						<td><span id="11_10" onclick="selectLED(11,10);">186</span></td>
						<td><span id="11_11" onclick="selectLED(11,11);">187</span></td>
						<td><span id="11_12" onclick="selectLED(11,12);">188</span></td>
						<td><span id="11_13" onclick="selectLED(11,13);">189</span></td>
						<td><span id="11_14" onclick="selectLED(11,14);">190</span></td>
						<td><span id="11_15" onclick="selectLED(11,15);">191</span></td>
                    </tr>
                    <tr>
						<td><span id="12_0" onclick="selectLED(12,0);">192</span></td>
						<td><span id="12_1" onclick="selectLED(12,1);">193</span></td>
						<td><span id="12_2" onclick="selectLED(12,2);">194</span></td>
						<td><span id="12_3" onclick="selectLED(12,3);">195</span></td>
						<td><span id="12_4" onclick="selectLED(12,4);">196</span></td>
						<td><span id="12_5" onclick="selectLED(12,5);">197</span></td>
						<td><span id="12_6" onclick="selectLED(12,6);">198</span></td>
						<td><span id="12_7" onclick="selectLED(12,7);">199</span></td>
                        <td><span id="12_8" onclick="selectLED(12,8);">200</span></td>
						<td><span id="12_9" onclick="selectLED(12,9);">201</span></td>
						<td><span id="12_10" onclick="selectLED(12,10);">202</span></td>
						<td><span id="12_11" onclick="selectLED(12,11);">203</span></td>
						<td><span id="12_12" onclick="selectLED(12,12);">204</span></td>
						<td><span id="12_13" onclick="selectLED(12,13);">205</span></td>
						<td><span id="12_14" onclick="selectLED(12,14);">206</span></td>
						<td><span id="12_15" onclick="selectLED(12,15);">207</span></td>
                    </tr>
                    <tr>
						<td><span id="13_0" onclick="selectLED(13,0);">208</span></td>
						<td><span id="13_1" onclick="selectLED(13,1);">209</span></td>
						<td><span id="13_2" onclick="selectLED(13,2);">210</span></td>
						<td><span id="13_3" onclick="selectLED(13,3);">211</span></td>
						<td><span id="13_4" onclick="selectLED(13,4);">212</span></td>
						<td><span id="13_5" onclick="selectLED(13,5);">213</span></td>
						<td><span id="13_6" onclick="selectLED(13,6);">214</span></td>
						<td><span id="13_7" onclick="selectLED(13,7);">215</span></td>
                        <td><span id="13_8" onclick="selectLED(13,8);">216</span></td>
						<td><span id="13_9" onclick="selectLED(13,9);">217</span></td>
						<td><span id="13_10" onclick="selectLED(13,10);">218</span></td>
						<td><span id="13_11" onclick="selectLED(13,11);">219</span></td>
						<td><span id="13_12" onclick="selectLED(13,12);">220</span></td>
						<td><span id="13_13" onclick="selectLED(13,13);">221</span></td>
						<td><span id="13_14" onclick="selectLED(13,14);">222</span></td>
						<td><span id="13_15" onclick="selectLED(13,15);">223</span></td>
                    </tr>
                    <tr>
						<td><span id="14_0" onclick="selectLED(14,0);">224</span></td>
						<td><span id="14_1" onclick="selectLED(14,1);">225</span></td>
						<td><span id="14_2" onclick="selectLED(14,2);">226</span></td>
						<td><span id="14_3" onclick="selectLED(14,3);">227</span></td>
						<td><span id="14_4" onclick="selectLED(14,4);">228</span></td>
						<td><span id="14_5" onclick="selectLED(14,5);">229</span></td>
						<td><span id="14_6" onclick="selectLED(14,6);">230</span></td>
						<td><span id="14_7" onclick="selectLED(14,7);">231</span></td>
                        <td><span id="14_8" onclick="selectLED(14,8);">232</span></td>
						<td><span id="14_9" onclick="selectLED(14,9);">233</span></td>
						<td><span id="14_10" onclick="selectLED(14,10);">234</span></td>
						<td><span id="14_11" onclick="selectLED(14,11);">235</span></td>
						<td><span id="14_12" onclick="selectLED(14,12);">236</span></td>
						<td><span id="14_13" onclick="selectLED(14,13);">237</span></td>
						<td><span id="14_14" onclick="selectLED(14,14);">238</span></td>
						<td><span id="14_15" onclick="selectLED(14,15);">239</span></td>
                    </tr>
                    <tr>
						<td><span id="15_0" onclick="selectLED(15,0);">240</span></td>
						<td><span id="15_1" onclick="selectLED(15,1);">241</span></td>
						<td><span id="15_2" onclick="selectLED(15,2);">242</span></td>
						<td><span id="15_3" onclick="selectLED(15,3);">243</span></td>
						<td><span id="15_4" onclick="selectLED(15,4);">244</span></td>
						<td><span id="15_5" onclick="selectLED(15,5);">245</span></td>
						<td><span id="15_6" onclick="selectLED(15,6);">246</span></td>
						<td><span id="15_7" onclick="selectLED(15,7);">247</span></td>
                        <td><span id="15_8" onclick="selectLED(15,8);">248</span></td>
						<td><span id="15_9" onclick="selectLED(15,9);">249</span></td>
						<td><span id="15_10" onclick="selectLED(15,10);">250</span></td>
						<td><span id="15_11" onclick="selectLED(15,11);">251</span></td>
						<td><span id="15_12" onclick="selectLED(15,12);">252</span></td>
						<td><span id="15_13" onclick="selectLED(15,13);">253</span></td>
						<td><span id="15_14" onclick="selectLED(15,14);">254</span></td>
						<td><span id="15_15" onclick="selectLED(15,15);">255</span></td>
                    </tr>					
				</tbody>
				<tfoot>				
				</tfoot>
			</table>
		</fieldset>
	<div id="ledEdit" style="display:none;">
		<form id="configForm" name="configForm" class="configForm"  method="POST" action="#" enctype="multipart/form-data" target="_self">
		<fieldset id="coilsFieldset">
		  <legend id="formLegend"> LED Edit:: </legend>
			<table id="ledEditTable">
				<thead>
					<tr>
						<th>Element</th>
						<th>Setting Value</th>
					</tr>
					
				</thead>
				<tbody>
					<tr>
						<td><label for="ledId">LED ID</label></td>
						<td><input type="text" id="ledId" value="-1"></td>
					</tr>
					<tr>
						<td><label for="ledName">LED Name</label></td>
						<td><input type="text" id="ledName" value=""></td>
					</tr>
					<tr>
						<td><label for="ledColour">LED Colour</label></td>
						<td><input type="text" id="ledColour" value="" data-coloris></td>
					</tr>
					<tr>
						<td><label for="ledIsOn">Is On?</label></td>
						<td><input type="checkbox" id="ledIsOn" name="ledIsOn" value="true"></td>
					</tr>
					<tr>
						<td><label for="ledFlashSpeed">Flash Speed (flash per second)</label></td>
						<td><input type="text" id="ledFlashSpeed" value="0"></td>
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

)=====";