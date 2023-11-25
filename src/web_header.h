#include <Arduino.h>
const char html_header[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<title>ESP32 Pinball OS - Firmware Upload</title>
<meta charset='UTF-8'>
<meta name='viewport' content='width=device-width, initial-scale=1'>
<link rel='stylesheet' href='./css/w3c.css'>
<!--<link rel='stylesheet' href='https://fonts.googleapis.com/css?family=Raleway'>-->
<!--<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css'>-->
<style>
html,body,h1,h2,h3,h4,h5 {font-family: 'Raleway', sans-serif}
</style>
<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>
</head>
<body class='w3-light-grey'>

<!-- Top container -->
<div class='w3-bar w3-top w3-black w3-large' style='z-index:4'>
  <button class='w3-bar-item w3-button w3-hide-large w3-hover-none w3-hover-text-light-grey' onclick='w3_open();'><i class='fa fa-bars'></i>  Menu</button>
  <span class='w3-bar-item w3-right'>ESP32 Pinball OS</span>
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
    <a href='./action/solenoidTest' class='w3-bar-item w3-button w3-padding w3-blue'><i class='fa fa-wrench fa-fw'></i>Solenoid Test</a>
    <a href='./config' class='w3-bar-item w3-button w3-padding w3-blue'><i class='fa fa-wrench fa-fw'></i>Config</a>
  </div>
</nav>


<!-- Overlay effect when opening sidebar on small screens -->
<div class='w3-overlay w3-hide-large w3-animate-opacity' onclick='w3_close()' style='cursor:pointer' title='close side menu' id='myOverlay'></div>

<!-- !PAGE CONTENT! -->
<div class='w3-main' style='margin-left:300px;margin-top:43px;'>
)=====";