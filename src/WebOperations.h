#include <Arduino.h>
#include <WebServer.h>
#include <Update.h>
#include <ArduinoJson.h>

#include "web_dashboard.h"
#include "web_config.h"
#include "web_upload.h"
#include "web_css.h"
#include "web_jquery.h"
#include "web_header.h"
#include "web_footer.h"


WebServer server(80);



void WebOperationsFunction( void * pvParameters);

void web_handle_AJAXState();
void web_handle_AJAXCPU0Hz();
void web_handle_AJAXCPU1Hz();
void web_handle_AJAXPlayerNumber();
void web_handle_AJAXBallNumber();
void web_handle_AJAXPlayerScore();
void web_handle_AJAXBallSave();
void web_handle_AJAXTopDisplay();
void web_handle_AJAXBottomDisplay();
void web_handle_AJAXP1Score();
void web_handle_AJAXP2Score();
void web_handle_AJAXP3Score();
void web_handle_AJAXP4Score();
void web_handle_AJAXP1Ball();
void web_handle_AJAXP2Ball();
void web_handle_AJAXP3Ball();
void web_handle_AJAXP4Ball();

void web_handle_AJAXConfig();

void web_handle_captive_toLocalIP();
void web_handle_captive_connecttest();//[](AsyncWebServerRequest *request) { request->redirect("http://logout.net"); });	// windows 11 captive portal workaround
void web_handle_captive_ffx2();//[](AsyncWebServerRequest *request) { request->send(200); });					   // firefox captive portal call home

void web_handle_viewState();
void web_handle_404();
void web_handle_config();
void web_handle_firmwareUpload();
void web_handle_css();
void web_handle_js();

bool web_handle_configUpdate();

void web_handle_switchDebug();
void web_handle_coilDebug();
void web_handle_opsDebug();


void web_handle_action_startbutton();
void web_handle_action_restart();
void web_handle_action_outholeswitch();
void web_handle_action_rolloverswitch();
void web_handle_action_leftrolloverswitch();
void web_handle_action_rightrolloverswitch();
void web_handle_action_leftpopswitch();
void web_handle_action_rightpopswitch();
void web_handle_action_spinnerswitch();
void web_handle_action_leftoutlaneswitch();
void web_handle_action_rightoutlaneswitch();
void web_handle_action_leftinlaneswitch();
void web_handle_action_rightinlaneswitch();
void web_handle_action_lefttoplaneswitch();
void web_handle_action_righttoplaneswitch();
void web_handle_action_centertoplaneswitch();
void web_handle_action_saucerswitch();
void web_handle_action_standup1switch();
void web_handle_action_standup2switch();
void web_handle_action_standup3switch();
void web_handle_action_standup4switch();
void web_handle_action_standup5switch();
void web_handle_action_drop1switch();
void web_handle_action_drop2switch();
void web_handle_action_drop3switch();
void web_handle_action_drop4switch();
void web_handle_action_drop5switch();

void web_handle_action_solenoidTest();


//setup a task to run on core 0;
TaskHandle_t WebOperationsTask;


void WebOperationsFunction( void * pvParameters)
{
    int counterWeb = 0;
    unsigned long lastMillisWeb = 0;
    //Setup functions
    //captive portal pages
    // Required
    server.on("/connecttest.txt", web_handle_captive_connecttest);//[](AsyncWebServerRequest *request) { request->redirect("http://logout.net"); });	// windows 11 captive portal workaround
    server.on("/wpad.dat", web_handle_404);//[](AsyncWebServerRequest *request) { request->send(404); });								// Honestly don't understand what this is but a 404 stops win 10 keep calling this repeatedly and panicking the esp32 :)

    // Background responses: Probably not all are Required, but some are. Others might speed things up?
    // A Tier (commonly used by modern systems)
    server.on("/generate_204", web_handle_captive_toLocalIP);//[](AsyncWebServerRequest *request) { request->redirect(localIPURL); });		   // android captive portal redirect
    server.on("/redirect", web_handle_captive_toLocalIP);//[](AsyncWebServerRequest *request) { request->redirect(localIPURL); });			   // microsoft redirect
    server.on("/hotspot-detect.html", web_handle_captive_toLocalIP);//[](AsyncWebServerRequest *request) { request->redirect(localIPURL); });  // apple call home
    server.on("/canonical.html", web_handle_captive_toLocalIP);//[](AsyncWebServerRequest *request) { request->redirect(localIPURL); });	   // firefox captive portal call home
    server.on("/success.txt", web_handle_captive_ffx2);//[](AsyncWebServerRequest *request) { request->send(200); });					   // firefox captive portal call home
    server.on("/ncsi.txt", web_handle_captive_toLocalIP);//[](AsyncWebServerRequest *request) { request->redirect(localIPURL); });			   // windows call home
    
    
    //Actual Web Pages
    server.on("/viewState", web_handle_viewState);
    server.on("/config", web_handle_config);
    server.on("/uploadDev", web_handle_firmwareUpload);

    //CSS
     server.on("/css/w3c.css", web_handle_css);

    //JS
     server.on("/js/jquery.js", web_handle_js);

    //AJAX calls
    server.on("/ajax_getState",  web_handle_AJAXState);
    server.on("/ajax_getCPU0",  web_handle_AJAXCPU0Hz);
    server.on("/ajax_getCPU1",  web_handle_AJAXCPU1Hz);
    server.on("/ajax_getPlayerNumber",  web_handle_AJAXPlayerNumber);
    server.on("/ajax_getBallNumber",  web_handle_AJAXBallNumber);
    server.on("/ajax_getPlayerScore",  web_handle_AJAXPlayerScore);
    server.on("/ajax_getBallSave",  web_handle_AJAXBallSave);
    server.on("/ajax_getTopDisplay",  web_handle_AJAXTopDisplay);
    server.on("/ajax_getBottomDisplay",  web_handle_AJAXBottomDisplay);
    server.on("/ajax_getP1Score",  web_handle_AJAXP1Score);
    server.on("/ajax_getP2Score",  web_handle_AJAXP2Score);
    server.on("/ajax_getP3Score",  web_handle_AJAXP3Score);
    server.on("/ajax_getP4Score",  web_handle_AJAXP4Score);
    server.on("/ajax_getP1Ball",  web_handle_AJAXP1Ball);
    server.on("/ajax_getP2Ball",  web_handle_AJAXP2Ball);
    server.on("/ajax_getP3Ball",  web_handle_AJAXP3Ball);
    server.on("/ajax_getP4Ball",  web_handle_AJAXP4Ball);
    server.on("/ajax_getConfig",  web_handle_AJAXConfig);

    //Toggle the debug messgaes seen on serial
    server.on("/debug/switch", web_handle_switchDebug);
    server.on("/debug/coil", web_handle_coilDebug);
    server.on("/debug/ops", web_handle_opsDebug);
  
    //some virtual buttons to do work 
    server.on("/action/startbutton", web_handle_action_startbutton);
    server.on("/action/outholeswitch", web_handle_action_outholeswitch);
    server.on("/action/rolloverswitch", web_handle_action_rolloverswitch);
    server.on("/action/restart", web_handle_action_restart);    
   
    server.on("/action/leftrolloverswitch", web_handle_action_leftrolloverswitch);
    server.on("/action/rightrolloverswitch", web_handle_action_rightrolloverswitch);
    server.on("/action/leftpopswitch", web_handle_action_leftpopswitch);
    server.on("/action/rightpopswitch", web_handle_action_rightpopswitch);
    server.on("/action/spinnerswitch", web_handle_action_spinnerswitch);
    server.on("/action/leftoutlaneswitch", web_handle_action_leftoutlaneswitch);
    server.on("/action/rightoutlaneswitch", web_handle_action_rightoutlaneswitch);
    server.on("/action/leftinlaneswitch", web_handle_action_leftinlaneswitch);
    server.on("/action/rightinlaneswitch", web_handle_action_rightinlaneswitch);
    server.on("/action/lefttoplaneswitch", web_handle_action_lefttoplaneswitch);
    server.on("/action/righttoplaneswitch", web_handle_action_righttoplaneswitch);
    server.on("/action/centertoplaneswitch", web_handle_action_centertoplaneswitch);
    server.on("/action/saucerswitch", web_handle_action_saucerswitch);
    server.on("/action/standup1switch", web_handle_action_standup1switch);
    server.on("/action/standup2switch", web_handle_action_standup2switch);
    server.on("/action/standup3switch", web_handle_action_standup3switch);
    server.on("/action/standup4switch", web_handle_action_standup4switch);
    server.on("/action/standup5switch", web_handle_action_standup5switch);
    server.on("/action/drop1switch", web_handle_action_drop1switch);
    server.on("/action/drop2switch", web_handle_action_drop2switch);
    server.on("/action/drop3switch", web_handle_action_drop3switch);
    server.on("/action/drop4switch", web_handle_action_drop4switch);
    server.on("/action/drop5switch", web_handle_action_drop5switch);
    server.on("/action/solenoidTest", web_handle_action_solenoidTest);


    server.on("/", web_handle_viewState);
    server.on("/updateConfig", HTTP_POST, web_handle_configUpdate);
    server.onNotFound(web_handle_404);
        /*handling uploading firmware file */
    server.on("/update", HTTP_POST, []() {
        server.sendHeader("Connection", "close");
        server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
        delay(50); //give some time for web page to start reload
        ESP.restart();
    }, []() {
        HTTPUpload& upload = server.upload();
        if (upload.status == UPLOAD_FILE_START) {
        Serial.printf("Update: %s\n", upload.filename.c_str());
        if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
            Update.printError(Serial);
        }
        } else if (upload.status == UPLOAD_FILE_WRITE) {
        /* flashing firmware to ESP*/
        if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
            Update.printError(Serial);
        }
        } else if (upload.status == UPLOAD_FILE_END) {
        if (Update.end(true)) { //true to set the size to the current progress
            Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
        } else {
            Update.printError(Serial);
        }
        }
    });
    int WifiWaitCounter = 0;
    int MaxWait = 10;
    /*while ((WifiConnected != true) && (WifiWaitCounter < MaxWait)) {
      Serial.println("Webserver Waiting for Wifi");
      vTaskDelay(1000);
      WifiWaitCounter +=1;
    }
    if(WifiConnected ==  WL_CONNECTED)
    {
      server.begin();
      Serial.println("Webserver Started");
    }else
    {
      Serial.println("Webserver NOT Started");
      //Lets forget about wifi and webserver
      vTaskDelete(NULL);
    }*/
    while ((WifiConnected != true) && (wifiSoftAPInUse != true)) {
      Serial.println("Webserver Waiting for Wifi");
      vTaskDelay(1000);
      //WifiWaitCounter +=1;
    }
  
    server.begin();
    Serial.println("Webserver Started");
    
  bool clientConnected = false;
  bool lastConnectionStatus = false;

  for(;;){
    // count how many times we are scanning switch matrix per second, and display it, remove this debug message in live version
    counterWeb++;
    //static int tempSound=1;
    if (millis() - lastMillisWeb > 10000 ){
        if(loopDebug)
        {
          Serial.print("WebOperations : CORE ");
          Serial.print(xPortGetCoreID());
          Serial.print(" : is currently running at approimatly ");
          Serial.print(counterWeb/10);
          Serial.println("Hz (full program cycles per second)");
        }
      WEBHz = counterWeb/10;  
      counterWeb = 0;
      lastMillisWeb = millis();
    }
    // End of debug stuff 
      //webserver code
    if(WiFi.status() == WL_CONNECTED)
    {
        if(lastConnectionStatus == false)
        {
          Serial.println("Client Connected");
          lastConnectionStatus = true;
          clientConnected = true;
        }
    }else{
      //no client connected
      if(lastConnectionStatus == true)
        {
          Serial.println("Client Disconnected");
          lastConnectionStatus = false;
          clientConnected = false;
        }
    }
    if(wifiSoftAPInUse == true)
    {
      dnsServer.processNextRequest();
    }
    server.handleClient();
    
    vTaskDelay(2);
  }
}

/* START web page functions */
/* AJAX Calls */
void web_handle_AJAXState()
{
    String MachineStateWrite = "Booting";
    switch(MachineState){
      case 0: //Bootup
          {
            MachineStateWrite = "Booting";
            break;
          }
      case 1: //Atract
          {
            MachineStateWrite = "Atract";
            break;
          }
      case 2: //Game
          {
            MachineStateWrite = "Game";
            break;
          }
      case 3: //End of game
          {
            MachineStateWrite = "End Game";
            break;
          }
    }
    server.send(200, "text/plain", MachineStateWrite); //Send ADC value only to client ajax request
}
void web_handle_AJAXCPU0Hz()
{
    server.send(200, "text/plain", (String)CMOHz); //Send ADC value only to client ajax request
}
void web_handle_AJAXCPU1Hz()
{
    server.send(200, "text/plain", (String)WEBHz); //Send ADC value only to client ajax request
}
void web_handle_AJAXPlayerNumber()
{
  String PlayerNmuberText = (String)g_myPinballGame.getCurrentPlayerNumber() + " of " + (String)g_myPinballGame.getCurrentPlayerNumbers();
  server.send(200, "text/plain", PlayerNmuberText);
}
void web_handle_AJAXBallNumber()
{
  server.send(200, "text/plain", (String)g_myPinballGame.getCurrentBallNumber(g_myPinballGame.getCurrentPlayerNumber()));
}
void web_handle_AJAXPlayerScore()
{
  server.send(200, "text/plain", (String)g_myPinballGame.getPlayerScore(g_myPinballGame.getCurrentPlayerNumber()));
}
void web_handle_AJAXBallSave()
{
  bool BallSaveActive = g_myPinballGame.isBallSave();
  String BallSaveTextReturn = "OFF";
  if(BallSaveActive == 1)
  {
    BallSaveTextReturn = "ON";
  }
  server.send(200, "text/plain", BallSaveTextReturn);
}
void web_handle_AJAXTopDisplay()
{
  server.send(200, "text/plain", (String)ScoreboardTText);
}
void web_handle_AJAXBottomDisplay()
{
  server.send(200, "text/plain", (String)ScoreboardBText);
}
void web_handle_AJAXP1Score()
{
  server.send(200, "text/plain", (String)g_myPinballGame.getPlayerScore(1));
}
void web_handle_AJAXP2Score()
{
  server.send(200, "text/plain", (String)g_myPinballGame.getPlayerScore(2));
}
void web_handle_AJAXP3Score()
{
  server.send(200, "text/plain", (String)g_myPinballGame.getPlayerScore(3));
}
void web_handle_AJAXP4Score()
{
  server.send(200, "text/plain", (String)g_myPinballGame.getPlayerScore(4));
}
void web_handle_AJAXP1Ball()
{
  server.send(200, "text/plain", (String)g_myPinballGame.getCurrentBallNumber(1));
}
void web_handle_AJAXP2Ball()
{
  server.send(200, "text/plain", (String)g_myPinballGame.getCurrentBallNumber(2));
}
void web_handle_AJAXP3Ball()
{
  server.send(200, "text/plain", (String)g_myPinballGame.getCurrentBallNumber(3));
}
void web_handle_AJAXP4Ball()
{
  server.send(200, "text/plain", (String)g_myPinballGame.getCurrentBallNumber(4));
}
void web_handle_AJAXConfig()
{
    String jsonConfig;
    File file = SPIFFS.open(localConfigFile);
    while (file.available()) {
        // Extract each characters by one by one
        jsonConfig = file.readString();
    }
    server.send(200, "text/plain", jsonConfig); //Send ADC value only to client ajax request
}
/* Button Actions */
void web_handle_switchDebug()
{
    Serial.println("[web_handle] Switch Debug Toggled");
    switchDebug = !switchDebug;
    //for each switch, update
    const int NumSwitches = tableCols * tableRows;
    for(int i=0; (int)NumSwitches > i; i++)
    {
      switches[i].switchObject->toggleDebug();
    }
    server.send(200, "text/html", "OK - Set to "  + (String)switchDebug); //Send web page
 
}
void web_handle_coilDebug()
{
    //There is no toggleDebug method within the coils - this needs fixing 
    Serial.println("[web_handle] Coil Debug Toggled - will have no effect until class updated");
    coilDebug = !coilDebug;
    server.send(200, "text/html", "OK - Set to " + (String)coilDebug); //Send web page
 
}
void web_handle_opsDebug()
{
    generalMODebug = !generalMODebug;
    Serial.println("[web_handle] Ops Debug Toggled");
    server.send(200, "text/html", "OK - Set to " + (String)generalMODebug); //Send web page
 
}
void web_handle_action_startbutton()
{
  Serial.println("[web_handle] start button switch");
  switch_event_startbutton();
  server.send(200, "text/html", "OK - Start Button Virtually Pressed"); //Send web page
 
}
void web_handle_action_outholeswitch()
{
  Serial.println("[web_handle] outhole switch");
  switch_event_outhole();
  server.send(200, "text/html", "OK - Outhole Switch Virtually Pressed"); //Send web page
}
void web_handle_action_rolloverswitch()
{
  Serial.println("[web_handle] center rollover switch");
  switch_event_rollover_center(27);
  server.send(200, "text/html", "OK - Center Rollover Virtually Pressed"); //Send web page
}

void web_handle_action_leftrolloverswitch()
{
  switch_event_rollover_left(12);
  server.send(200, "text/html", "OK - Switch Virtually Pressed"); //Send web page
}
void web_handle_action_rightrolloverswitch()
{
  switch_event_rollover_right(11);
  server.send(200, "text/html", "OK - Switch Virtually Pressed"); //Send web page
}

void web_handle_action_leftpopswitch()
{
  switch_event_pop(6);
  server.send(200, "text/html", "OK - Switch Virtually Pressed"); //Send web page
}
void web_handle_action_rightpopswitch()
{
  switch_event_pop(7);
  server.send(200, "text/html", "OK - Switch Virtually Pressed"); //Send web page
}
void web_handle_action_spinnerswitch()
{
  switch_event_spinner(24);
  server.send(200, "text/html", "OK - Switch Virtually Pressed"); //Send web page
}
void web_handle_action_leftoutlaneswitch()
{
  switch_event_outane_left(17);
  server.send(200, "text/html", "OK - Switch Virtually Pressed"); //Send web page
}
void web_handle_action_rightoutlaneswitch()
{
  switch_event_outane_right(16);
  server.send(200, "text/html", "OK - Switch Virtually Pressed"); //Send web page
}
void web_handle_action_leftinlaneswitch()
{
  switch_event_lane_c(23);
  server.send(200, "text/html", "OK - Switch Virtually Pressed"); //Send web page
}
void web_handle_action_rightinlaneswitch()
{
  switch_event_lane_p(19);
  server.send(200, "text/html", "OK - Switch Virtually Pressed"); //Send web page
}
void web_handle_action_lefttoplaneswitch()
{
  switch_event_lane_h(22);
  server.send(200, "text/html", "OK - Switch Virtually Pressed"); //Send web page
}
void web_handle_action_righttoplaneswitch()
{
  switch_event_lane_m(20);
  server.send(200, "text/html", "OK - Switch Virtually Pressed"); //Send web page
}
void web_handle_action_centertoplaneswitch()
{
  switch_event_lane_a(21);
  server.send(200, "text/html", "OK - Switch Virtually Pressed"); //Send web page
}
void web_handle_action_saucerswitch()
{
  switch_event_saucer(3);
  server.send(200, "text/html", "OK - Switch Virtually Pressed"); //Send web page
}
void web_handle_action_standup1switch()
{
  switch_event_standup_e(39);
  server.send(200, "text/html", "OK - Switch Virtually Pressed"); //Send web page
}
void web_handle_action_standup2switch()
{
  switch_event_standup_i(38);
  server.send(200, "text/html", "OK - Switch Virtually Pressed"); //Send web page
}
void web_handle_action_standup3switch()
{
  switch_event_standup_g(37);
  server.send(200, "text/html", "OK - Switch Virtually Pressed"); //Send web page
}
void web_handle_action_standup4switch()
{
  switch_event_standup_h(36);
  server.send(200, "text/html", "OK - Switch Virtually Pressed"); //Send web page
}
void web_handle_action_standup5switch()
{
  switch_event_standup_t(35);
  server.send(200, "text/html", "OK - Switch Virtually Pressed"); //Send web page
}
void web_handle_action_drop1switch()
{
  switch_event_drop1(31);
  server.send(200, "text/html", "OK - Switch Virtually Pressed"); //Send web page
}
void web_handle_action_drop2switch()
{
  switch_event_drop2(29);
  server.send(200, "text/html", "OK - Switch Virtually Pressed"); //Send web page
}
void web_handle_action_drop3switch()
{
  switch_event_drop3(28);
  server.send(200, "text/html", "OK - Switch Virtually Pressed"); //Send web page
}
void web_handle_action_drop4switch()
{
  switch_event_drop4(26);
  server.send(200, "text/html", "OK - Switch Virtually Pressed"); //Send web page
}
void web_handle_action_drop5switch()
{
  switch_event_drop5(25);
  server.send(200, "text/html", "OK - Switch Virtually Pressed"); //Send web page
}

void web_handle_action_solenoidTest()
{
  //for each coil, fire it
  String webText = "";
  for(char coilNumber = 1; coilNumber < coilCount; coilNumber++)
  {
    delay(1000);
    PinballCoil* thisCoil = coils[coilNumber].coilObject; //get the PinballCoil instance associated
    Serial.print("Solenod Test : ");
    thisCoil->fireCoil();
    Serial.println(thisCoil->getName());
    ProcessShifts(thisCoil); //set shift register bytes to turn on solenoid
    //delay(1000);
    write_sr_coils();
    //delay(1000);
    coilActive[coilNumber]=true;//leave a flag to processing the turning off of the coil - this gets done in managecoils()
   
  }
   server.send(200, "text/html", "OK - SolenoidTest Complete"); //Send web page
}


void web_handle_action_restart()
{
    ESP.restart();
 
}
/* Page Calls*/
void web_handle_viewState()
{
  // calculate the required buffer size (also accounting for the null terminator):
  int bufferSize = strlen(html_header) + strlen(MAIN_page) + strlen(html_footer) + strlen(liveview_script_footer) + 1;

  // allocate enough memory for the concatenated string:
  char* concatString = new char[ bufferSize ];

  // copy strings one and two over to the new buffer:
  strcpy( concatString, html_header );
  strcat( concatString, MAIN_page );
  strcat( concatString, html_footer );
  strcat( concatString, liveview_script_footer );

  server.send(200, "text/html", concatString); //Send web page
  delete[] concatString;
 
}
void web_handle_404()
{
    String s = "<!DOCTYPE html> <html><body><h1>404</h1></body></html>"; //Read HTML contents
    server.send(404, "text/html", s); //Send web page
 
}

bool web_handle_configUpdate()
{
  if(server.args() == 0)
  {
    return false; //no JSON no webpage my friend ;)
  }
  Serial.println("plain: " + server.arg("plain"));
  DynamicJsonDocument postedJSON(2048);
  deserializeJson(postedJSON,server.arg("plain"));
  Serial.println((const char*)postedJSON["Name"]);
  Serial.println((const char*)postedJSON["Version"]);
  setting_MachineName = (const char*)postedJSON["Name"];
  setting_MachineVersion = (const char*)postedJSON["Version"];
  setting_SSID = (const char*)postedJSON["SSID"];
  setting_SSIDPassword = (const char*)postedJSON["SSIDPassword"];
  updateConfigFiles();
  return true;
}


void web_handle_config()
{
    String s = CONFIG_page; //Read HTML contents
    server.send(200, "text/html", s); //Send web page
 
}
void web_handle_firmwareUpload()
{
  
  // calculate the required buffer size (also accounting for the null terminator):
  int bufferSize = strlen(html_header) + strlen(UPLOAD_page) + strlen(html_footer) + strlen(upload_script_footer) + 1;

  // allocate enough memory for the concatenated string:
  char* concatString = new char[ bufferSize ];

  // copy strings one and two over to the new buffer:
  strcpy( concatString, html_header );
  strcat( concatString, UPLOAD_page );
  strcat( concatString, html_footer );
  strcat( concatString, upload_script_footer );

  server.send(200, "text/html", concatString); //Send web page
  delete[] concatString;
}
void web_handle_captive_connecttest()
{
    //[](AsyncWebServerRequest *request) { request->redirect("http://logout.net"); });	// windows 11 captive portal workaround
    server.sendHeader("Location", "http://logout.net",true);
    server.send(302, "text/plain", "");
}
void web_handle_captive_wpad()
{
    //[](AsyncWebServerRequest *request) { request->send(404); }); //Windows proxy check, 404 staps it asking
    web_handle_404();
}								
void web_handle_captive_toLocalIP()
{
  //[](AsyncWebServerRequest *request) { request->redirect(localIPURL); });		   // android captive portal redirect
    String localIPURL = "http://" + localIP.toString();
    server.sendHeader("Location", localIPURL,true);
    server.send(302, "text/plain", "");

}

void  web_handle_captive_ffx2()
{
    //[](AsyncWebServerRequest *request) { request->send(200); });					   // firefox captive portal call home
    String s = ""; //Read HTML contents
    server.send(200, "text/html", s); //Send web page
}

void web_handle_css()
{
    String s = W3C_CSS; //Read HTML contents
    server.send(200, "text/css", s); //Send web page
}

void web_handle_js()
{
    String s = W3C_JQUERY; //Read HTML contents
    server.send(200, "text/javascript", s); //Send web page
}


/* END web page functions */

