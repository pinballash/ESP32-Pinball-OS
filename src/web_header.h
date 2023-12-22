#include <Arduino.h>
const char html_header[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<title>ESP32 Pinball OS</title>
<meta charset='UTF-8'>
<meta name='viewport' content='width=device-width, initial-scale=1'>
<link rel='stylesheet' href='./css/w3c.css'>
<link rel='stylesheet' href='https://fonts.googleapis.com/css?family=Raleway'>
<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css'>
<style>
html,body,h1,h2,h3,h4,h5 {font-family: 'Raleway', sans-serif}
</style>
<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>
</head>
<body class='w3-light-grey' onload="loadPage();">

<!-- Top container -->
<div class='w3-bar w3-top w3-black w3-large' style='z-index:4'>
  <button class='w3-bar-item w3-button w3-hide-large w3-hover-none w3-hover-text-light-grey' onclick='w3_open();'><i class='fa fa-bars'></i>  Menu</button>
  <span class='w3-bar-item w3-right'>
    <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACgAAAAoCAYAAACM/rhtAAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAAAJcEhZcwAADsEAAA7BAbiRa+0AAABhaVRYdFNuaXBNZXRhZGF0YQAAAAAAeyJjbGlwUG9pbnRzIjpbeyJ4IjowLCJ5IjowfSx7IngiOjExNywieSI6MH0seyJ4IjoxMTcsInkiOjExOX0seyJ4IjowLCJ5IjoxMTl9XX1ZSMW7AAAJQUlEQVRYR82ZBYhV3RbH94zd3TVjdyv2WIyJhQoGJoqKBXZ3gYUtiAEqJmKiGCiM3d3d3R37W7/lPYdz7z3q88H3eH/Yc85dZ8faq/eeCGOMlRaEhAkTmnLlyul7smTJzPfv382bN2/MqVOnTK5cuUx0dLSJFy+euX//vrl48aIpW7as/qZvRESEuXXrlrl8+bKJiooyuXPnVtqLFy/MyZMnTeLEiU3JkiVN0qRJdV76PXr0SNf6FWAwqMWPH99u2rTJgvPnz1uZQN8bNGhgHz58aB8/fmyvXbumtBo1atjFixfruzBr7969a79+/er2FSbsu3fv9Hu9evVs//799f3t27f6PHjwYNj63hYpf8Lw7ds3c+jQIfPs2TNTpEgRM2jQIKV/+fLFpEmTxnTq1MkUKFBAaZkzZ9a+79+/N8WLFzcxMTEqzRw5cpiMGTOapk2bmgwZMuicSA6pXr16Vb/Pnz/fZM+eXef5FXwZBKgZFYC4uDgTGxurKkqUKJEuxrcFCxaYly9fqrp+/Pih9E+fPulGIiMj9XnmzBlVq2jFiGT1KZI1r169UgH8J/AV7ZgxY6zYmL7nzJlTn6lTp7YfP360Z8+etUWLFlWa2JcdPXq0qozfIjVVXevWrW3FihWtSNsKI1YYtVmyZLElSpSwIjXtu2vXLnvnzh19/03zJdrhw4errS1btkyfIgWlV6lSRSfFtrp06aK0UaNG2efPn9v8+fPbzZs36ybEmfTbhQsX1BZFrbZUqVLu/GPHjtWNtG3b1qX9ovkSXWPGwDt27Kg0sS19Jk+e3K5du1a/V6pUyXbr1s2KOu3nz5+tmIEVr3bnSZ8+vRUbtK9fv7YrVqxQGhsDrOH0+03zJdoRI0bopJkyZdLfffr0sbVr17b79+93pSM2Z1u2bKkLig2qVJxNJEmSxI4fP941hUuXLtl58+apBsDs2bOV/qf2SyeROYxIz4h6Ta1atczMmTNN2rRpjUjM5MmTR/tg9DgHXis2aEaOHOk6Fl46bNgw9XKAc+A0rVq1Uifp3bu30suXL28SJEig737wZZAFCS9Zs2Y1okozbdo0pYttaTiZNGmS2bhxo3onDBFeUqZM6TIOYB6sWbPGSMzUb4yFSXEWDdD37t0zonZ3U37wzSSEksaNGysDxClRtYaFrVu3mgoVKphChQqp5J4+faq06tWrm1SpUpndu3drdgFsslmzZhoD0caHDx/Mzp07lTmk5oAMs3r16sCvcEQQCpgAZohdkgnM7du3Td68eTWu8Rt1weCTJ090EIuK8WsMlNCjqYyGCaDq06dPaz9AsCa4M9fNmzd1Y8DZJJIEjC9durTGVEwAqSvmzJkDgxo6SGl4bd26de3hw4c1tuXLl0/TkUjAiprUcIltoHPnzurBgFBCmsNZOnTo4Br53Llz9bswZyVXK41YKZtTmkheacRTp2+TJk3c8ZHr16+X509jFQ/ThJ8uXTrNAOyEtHTgwAEjXml69eqlfYVhVRv0vXv3Kq1hw4amYMGCmh2wyVAgQewPoAnJ8SolzAc484Fjx47pE0Q6KQ11MTlip2FDDhA/IAdja/RnQsbSwIMHD9QJAKbiPNk0uRqzkJCjdAdOPwd4OnDmBNoDBliQHTIIt+e3AwZgzClSpDBdu3bV8OMFDGfLls0sXLhQJY3nA0mRpnDhwhqiyNFi70r/GyiDhASMfeLEiUq8cuVKUGxi0RMnTpjly5ebfv366cKOupA2G0TVMM84mAWVK1fWDW/ZskUdR2xb6X+DSJhDnUwgCV5DAyohrjmAARaSzGAks5ju3bsHSZFvS5cuNZKLjRQSZurUqUon/PCbsIUnU9g6avSDY0rOE0SiSgYRw1DHhg0b9IO3E0C9hAQCb7t27XQDqNaxoylTpqhDbdu2Tc2D8WXKlNG4hzNINNCQgyOFok6dOqZatWruptEOIWvgwIE/VcxCEhqC6jPHWYDjFGDy5Mn6xC6hORnDUTmMSdGgKQ5mGIvkpczSdxgBzE1mAkhfKnM9VgBib/v27XXTxqlaZDI39ojKrdicFa/UOLVv3z6t6SSI6nfJHjqmWLFitlGjRvpOdUNMpTSjohkwYIDSpaJ25xUGtC4U6dgbN25oMeLEvsGDB7sxlSMERwrZtI0nahh9/PhxzYs0gDpR4ZEjRzR8yBiNi8QuMgWHJ7wax+BQhOqRCKZy9OhRs2TJEnUW7Jq+SIQwg2QxAzSFtJiTzLFjxw4jxavGYNZAO+fOnTOrVq3yz8X/T/ifMCgFrhYdOBRFA8fSv4FrI6GNM0jNmjXVzqR48O3zuybhxY4bN07tzQF2vWfPHiue6zvGp/kStUqWqiYwrdViYd26de4B6k+Ninr79u2B0f5wjhJ/aOHENm3aBKYIB1UPEvUb521DhgwJjLAqQTYsgdvOmDEjQLV6uOKg5Tfe04IJhBJJdToB6pCy3bZo0cJKpaE0B5Jf3fLJb47r169rP057oeYxdOhQ/QYkvQZ982nBBA45Djj0OHTJrxq3vCDeSb4NGk+jhpSwo30WLVoU9p04SD0IMIPQ794WXO8IZEzgzWjMc0ApRSbwgqsMYqGcod2UB8jtTqrEa0NB9qE+BJx9+vbta8QZw9KrgyCOOaBzYQTICqhXSnH3HCxlk5VDU5ADATxTFtM58H45ryidKhuJedfAORxgTlw6AW8287Qwgm3evLkO8ANlOiW7VN1WMkaA+hOYQI8ePXSOCRMmBKjWxsXF2ZiYGBsVFWV79uzp3nZhBmyKyAA4H4XyIi2MoA1PxmNDwaTk1JUrV6o3c0US2k9OaeoYUiEFKD9BbvVCTEZvHViPQ72YTBgf0sIIbkM1JHskhbr9IDnTSv3o3vc5INlLAWtnzZqlhYYX3DJMnz5d35FudHS07/qB5ksMa+xU6kC9HCL8hAJphAJpE45QHRmpfv36tmrVqm5VFBsbq8xj19yGha4ZaL7E3zaOn+J5uns/xkKB04U6Co7Ek8slOdBrPzkrB/UJtDDCXzWu1LhLpM77HbhY8o4jF2Me1J5kEyBH36A+gRZG+K8aC5HKMHY/58Ievf25KQNkI5IA+FcZ9DbUx7WcnE+sFLNqh1Q23j6BKxe9zkOSwLmq87Z/vR4kw1BthwI6/+rgiEqGonLnRkH4DPQAxvwDAjKd2kdBgZQAAAAASUVORK5CYII=" alt="ESP32 Pinball OS Logo" />
  </span>
</div>

<!-- Sidebar/menu -->
<nav class='w3-sidebar w3-collapse w3-white w3-animate-left' style='z-index:3;width:300px;' id='mySidebar'><br>
  <div class='w3-container'>
    <h5>Menu</h5>
  </div>
  <div class='w3-bar-block'>
    <a href='#' class='w3-bar-item w3-button w3-padding-16 w3-hide-large w3-dark-grey w3-hover-black' onclick='w3_close()' title='close menu'><i class='fa fa-remove fa-fw'></i>  Close Menu</a>
    <a href='./viewState' class='w3-bar-item w3-button w3-padding w3-blue'><i class='fa fa-play'></i> Live View</a>
    <a href='./uploadDev' class='w3-bar-item w3-button w3-padding w3-blue'><i class='fa fa-wrench fa-fw'></i>Update</a>
    <a href='./downloadConfig' class='w3-bar-item w3-button w3-padding w3-blue'><i class='fa fa-wrench fa-fw'></i>Download</a>
    <a href='./action/solenoidTest' class='w3-bar-item w3-button w3-padding w3-blue'><i class='fa fa-wrench fa-fw'></i>Solenoid Test</a>
    <a href='./config' class='w3-bar-item w3-button w3-padding w3-blue'><i class='fa fa-wrench fa-fw'></i>Basic Config</a>
    <a href='./config_switches' class='w3-bar-item w3-button w3-padding w3-blue'><i class='fa fa-wrench fa-fw'></i>Config Switches</a>
    <a href='./config_coils' class='w3-bar-item w3-button w3-padding w3-blue'><i class='fa fa-wrench fa-fw'></i>Config Coils</a>
    <a href='./config_switch_coil_binding' class='w3-bar-item w3-button w3-padding w3-blue'><i class='fa fa-wrench fa-fw'></i>Config Switch Coil Bindings</a>

  </div>
</nav>


<!-- Overlay effect when opening sidebar on small screens -->
<div class='w3-overlay w3-hide-large w3-animate-opacity' style='cursor:pointer; display:none;' title='loading' id='myLoadingOverlay'></div>
<div class='w3-overlay w3-hide-large w3-animate-opacity' onclick='w3_close()' style='cursor:pointer' title='close side menu' id='myOverlay'></div>

<!-- !PAGE CONTENT! -->
<div class='w3-main' style='margin-left:300px;margin-top:43px;'>
)=====";