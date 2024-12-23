
#include <Arduino.h>  //not needed in the arduino ide

// Captive Portal
//#include <AsyncTCP.h>  //https://github.com/me-no-dev/AsyncTCP using the latest dev version from @me-no-dev
#include <DNSServer.h>
#include <esp_wifi.h>			//Used for mpdu_rx_disable android workaround

// Pre reading on the fundamentals of captive portals https://textslashplain.com/2022/06/24/captive-portals/

const char *softAPssid = "ESP32Pinball-Configure-Me";  // FYI The SSID can't have a space in it.
// const char * password = "12345678"; //Atleast 8 chars
const char *softAPpassword = NULL;  // no password

#define MAX_CLIENTS 4	// ESP32 supports up to 10 but I have not tested it yet
#define WIFI_CHANNEL 6	// 2.4ghz channel 6 https://en.wikipedia.org/wiki/List_of_WLAN_channels#2.4_GHz_(802.11b/g/n/ax)

const IPAddress softAPlocalIP(4, 3, 2, 1);		   // the IP address the web server, Samsung requires the IP to be in public space
const IPAddress softAPgatewayIP(4, 3, 2, 1);		   // IP address of the network should be the same as the local IP for captive portals
const IPAddress softAPsubnetMask(255, 255, 255, 0);  // no need to change: https://avinetworks.com/glossary/subnet-mask/

DNSServer dnsServer;

void setUpDNSServer(DNSServer &dnsServer, const IPAddress &localIP) {
// Define the DNS interval in milliseconds between processing DNS requests
#define DNS_INTERVAL 30

	// Set the TTL for DNS response and start the DNS server
	dnsServer.setTTL(3600);
	dnsServer.start(53, "*", localIP);
}


void startSoftAccessPoint(const char *softAPssid, const char *softAPpassword, const IPAddress &softAPlocalIP, const IPAddress &softAPgatewayIP) {
// Define the maximum number of clients that can connect to the server
#define MAX_CLIENTS 4
// Define the WiFi channel to be used (channel 6 in this case)
#define WIFI_CHANNEL 6

	// Set the WiFi mode to access point and station
	WiFi.mode(WIFI_MODE_AP);

	// Define the subnet mask for the WiFi network
	const IPAddress subnetMask(255, 255, 255, 0);

	// Configure the soft access point with a specific IP and subnet mask
	WiFi.softAPConfig(softAPlocalIP, softAPgatewayIP, subnetMask);

	// Start the soft access point with the given ssid, password, channel, max number of clients
	WiFi.softAP(softAPssid, softAPpassword, WIFI_CHANNEL, 0, MAX_CLIENTS);

	// Disable AMPDU RX on the ESP32 WiFi to fix a bug on Android
	esp_wifi_stop();
	esp_wifi_deinit();
	wifi_init_config_t my_config = WIFI_INIT_CONFIG_DEFAULT();
	my_config.ampdu_rx_enable = false;
	esp_wifi_init(&my_config);
	esp_wifi_start();
	vTaskDelay(100 / portTICK_PERIOD_MS);  // Add a small delay
}