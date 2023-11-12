/*
* wireless networking settings
* Changes made 02/10/2023 - again
*/
const char* host = "ESPPOS"; //this will be the hostname on your network, but will be accessible as what you set + .local eg; yourPinballName.local
const char* ssid = "PinballWifi"; //This is the SSID of the wireless network in range of the pinball machine.
const char* password = "Flipp1nAw3s0me"; //this is the password to connect

const char* soft_ssid = "ESPPinballOS_AP"; //This is the SSID of the wireless network broadcast by the pinball machine is other connection not possible.
const char* soft_password = ""; //this is the password to connect