#include <Arduino.h>

void WiFiOperationsFunction( void * pvParameters);
TaskHandle_t WiFiOperationsTask;

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void printWifiSoftAPStatus()
{
  Serial.print("SSID: ");
  Serial.println(WiFi.softAPSSID());

  IPAddress ip = WiFi.softAPIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void WiFiOperationsFunction( void * pvParameters)
{
    Serial.print("Connecting to ");
    Serial.println(setting_SSID);
    WiFi.setHostname(host);
    WiFi.begin(setting_SSID, setting_SSIDPassword);
      // Wait for connection

      int WifiWaitCounter = 0;
      int MaxWait = 5;
  
      //g_myPinballGame.setDMDTopLine("Wi-Fi Connecting");
      while ((WiFi.status() != WL_CONNECTED) && (WifiWaitCounter < MaxWait)) 
      {
        delay(1000);
        //Serial.print(".");
        WifiWaitCounter++;
      }
        
      if(WiFi.status() ==  WL_CONNECTED)
      {
        WifiConnected = true;
        localIP = WiFi.localIP();
        //g_myPinballGame.setDMDTopLine("Connected           ");
        
        if (!MDNS.begin(host)) { //http://<host>.local
          while (1) {
            delay(1000);
          }
        }else{
          //g_myPinballGame.setDMDBottomLine(WiFi.localIP().toString());
          printWifiStatus();
        }
      }else
      {
        Serial.println("Starting Soft AP");
        startSoftAccessPoint(softAPssid, softAPpassword, softAPlocalIP, softAPgatewayIP);
        setUpDNSServer(dnsServer, softAPlocalIP);
        server.begin();
        localIP = WiFi.softAPIP();
        //g_myPinballGame.setDMDBottomLine(WiFi.softAPIP().toString());
        if (!MDNS.begin(host)) { //http://<host>.local
          while (1) {
            delay(1000);
          }
          
        }
        
        //g_myPinballGame.setDMDTopLine((String)localIP);
        delay(1000);
        wifiSoftAPInUse = true;
        
        //g_myPinballGame.setDMDBottomLine("SOFT AP ONLINE");
  }

    //in this function we just loop, check wifi is online, if not, we get online
    if(wifiSoftAPInUse == true)
    {
        
      Serial.println("Using Soft AP - pausing other processes");
      //vTaskSuspend(NULL);
      //vTaskDelete(NULL);
      vTaskSuspend(ProcessLeds);
      vTaskSuspend(ProcessSwitchesAndRules);
      vTaskSuspend(DisplayController);
      for(;;)
      {
          
          printWifiSoftAPStatus();
          vTaskDelay(pdMS_TO_TICKS(5000)); //yeild

      }
    }else{
          //first we make sure we arent in soft AP mode, if we are, we will kill ourself

          //now we loop
          for(;;)
          {
              if(WiFi.status() != WL_CONNECTED)
              {
                  //wifi disconnected, reconnect....
                  WiFi.disconnect();
                  WifiOnline = false;
                  //slowStreamError = true;
                  Serial.print("Connecting to ");
                  Serial.println(setting_SSID);
                  WiFi.begin(setting_SSID, setting_SSIDPassword);
                  WifiWaitCounter = 0;
                  MaxWait = 30;
              }
              while ((WiFi.status() != WL_CONNECTED) && (WifiWaitCounter < MaxWait)) 
              {
                  delay(1000);
                  //Serial.print(".");
                  WifiWaitCounter++;
              }
              if(WiFi.status() != WL_CONNECTED)
              {
                  //still disconnected? Reboot
                  Serial.print("WiFi unable to connect");
                  //esp_restart();

              }
              if(WifiOnline != true)
              {
                WifiOnline = true;
                printWifiStatus();
              }
              //printWifiStatus();
              vTaskDelay(pdMS_TO_TICKS(5000)); //yeild

          }

    }

}