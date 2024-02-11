#include <Arduino.h>
#include <WebServer.h>
#include <Update.h>
#include <ArduinoJson.h>

#include "web_dashboard.h"
#include "web_config.h"
#include "web_config_menu.h"
#include "web_config_switches.h"
#include "web_config_coils.h"
#include "web_config_switch_coil_binding.h"
#include "web_config_dummy.h"
#include "web_upload.h"
#include "web_download.h"
#include "web_css.h"
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
void web_handle_config_menu();


void web_handle_config_switches();
void web_handle_getSwitchConfig();
void web_handle_setSwitchConfig();

void web_handle_config_coils();
void web_handle_getCoilConfig();
void web_handle_setCoilConfig();

void web_handle_config_switchcoilbinding();
void web_handle_getswitchcoilbindingConfig();
void web_handle_setswitchcoilbindingConfig();

void web_handle_config_lighting();
void web_handle_getlightingConfig();
void web_handle_setlightingConfig();

void web_handle_config_titles();
void web_handle_gettitlesConfig();
void web_handle_settitlesConfig();

void web_handle_config_credits();
void web_handle_getcreditsConfig();
void web_handle_setcreditsConfig();

void web_handle_config_instructions();
void web_handle_getinstructionsConfig();
void web_handle_setinstructionsConfig();

void web_handle_config_modes();
void web_handle_getmodesConfig();
void web_handle_setmodesConfig();

void web_handle_listFS();
void web_handle_getFS();

void web_handle_firmwareUpload();
void web_handle_configDownload();
void web_handle_css();

bool web_handle_configUpdate();
void web_handle_switchDebug();
void web_handle_coilDebug();
void web_handle_opsDebug();

void web_handle_action_triggerswitch();
void web_handle_action_restart();

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
    server.on("/config_menu", web_handle_config_menu);
    server.on("/config_switches", web_handle_config_switches);
    server.on("/config_coils", web_handle_config_coils);
    server.on("/config_switch_coil_binding", web_handle_config_switchcoilbinding);
    server.on("/config_lighting", web_handle_config_lighting);
    server.on("/config_titles", web_handle_config_titles);
    server.on("/config_credits", web_handle_config_credits);
    server.on("/config_instructions", web_handle_config_instructions);
    server.on("/config_modes", web_handle_config_modes);
    server.on("/uploadDev", web_handle_firmwareUpload);
    server.on("/downloadConfig", web_handle_configDownload);

    //CSS
     server.on("/css/w3c.css", web_handle_css);

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
    server.on("/action/triggerswitch", web_handle_action_triggerswitch);
    server.on("/action/restart", web_handle_action_restart);    
    server.on("/action/solenoidTest", web_handle_action_solenoidTest);


    server.on("/", web_handle_viewState);
    server.on("/updateConfig", HTTP_POST, web_handle_configUpdate);
    
    //API Calls, get and set data 
    server.on("/api/switch/config/get", HTTP_POST, web_handle_getSwitchConfig);
    server.on("/api/switch/config/set", HTTP_POST, web_handle_setSwitchConfig);

    server.on("/api/fs/list", web_handle_listFS);
    server.on("/api/fs/get",HTTP_GET, web_handle_getFS);

    server.on("/api/switch/coil/config/get", HTTP_POST, web_handle_getswitchcoilbindingConfig);
    server.on("/api/switch/coil/config/set", HTTP_POST, web_handle_setswitchcoilbindingConfig);

    server.on("/api/coil/config/get", HTTP_POST, web_handle_getCoilConfig);
    server.on("/api/coil/config/set", HTTP_POST, web_handle_setCoilConfig);

    server.on("/api/lighting/config/get", HTTP_POST, web_handle_getlightingConfig);
    server.on("/api/lighting/config/set", HTTP_POST, web_handle_setlightingConfig);
	
    server.on("/api/titles/config/get", HTTP_POST, web_handle_gettitlesConfig);
    server.on("/api/titles/config/set", HTTP_POST, web_handle_settitlesConfig);
	
    server.on("/api/credits/config/get", HTTP_POST, web_handle_getcreditsConfig);
    server.on("/api/credits/config/set", HTTP_POST, web_handle_setcreditsConfig);

    server.on("/api/instructions/config/get", HTTP_POST, web_handle_getinstructionsConfig);
    server.on("/api/instructions/config/set", HTTP_POST, web_handle_setinstructionsConfig);

    server.on("/api/modes/config/get", HTTP_POST, web_handle_getmodesConfig);
    server.on("/api/modes/config/set", HTTP_POST, web_handle_setmodesConfig);



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

    while ((WifiConnected != true) && (wifiSoftAPInUse != true)) {
      //Serial.println("Webserver Waiting for Wifi");
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
    server.send(200, "text/plain", (String)reportedSwitchMatrixHz); //Send ADC value only to client ajax request
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
    Serial.println("[web_handle] Coil Debug Toggled");
    //for each coil - run the toggleDebug() method
    for ( byte col = 0; col < 2 ; col++) {
      for (byte row = 0; row < 8; row++) 
      {    
        int CoilIDInteger = (col * 8)+row;
        String CoilID = (String)CoilIDInteger;
        byte CoilByte = CoilIDInteger;

        
        PinballCoil* thisCoil = coils[CoilByte].coilObject;
        thisCoil->toggleDebug();
      }//end row processing
    }//end col processing
    server.send(200, "text/html", "OK"); //Send web page
 
}
void web_handle_opsDebug()
{
    generalMODebug = !generalMODebug;
    Serial.println("[web_handle] Ops Debug Toggled");
    server.send(200, "text/html", "OK - Set to " + (String)generalMODebug); //Send web page
 
}


void web_handle_action_triggerswitch()
{
  if(server.args() == 0)
  {
    Serial.println("No JSON in request"); //no JSON no webpage my friend ;)
    server.send(200, "text/plain", "{'Status' : 'FAIL'}"); //Send ADC value only to client ajax request
  }else{
    //Serial.println("SetSwitchConfig: plain: " + server.arg("plain"));
    DynamicJsonDocument postedJSON(2048);
    deserializeJson(postedJSON,server.arg("plain"));
    int jsoncol = postedJSON["col"];
    int jsonrow = postedJSON["row"];
    char col = jsoncol;
    char row = jsonrow;
    //Serial.println("Triggering Switch "+ server.arg("plain")); //no JSON no webpage my friend ;)
    switchActive[col][row]=true;
    server.send(200, "text/plain", "{'Status' : 'OK'}"); //Send ADC value only to client ajax request
  }
}

void web_handle_action_solenoidTest()
{
  //for each coil, fire it
  String webText = "";
  for(char coilNumber = 0; coilNumber < 16; coilNumber++)
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
    server.send(200, "text/plain", "{'Status' : 'OK - restarting'}"); //Send ADC value only to client ajax request
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

void web_handle_getSwitchConfig()
{
  if(server.args() == 0)
  {
    Serial.println("No JSON in request"); //no JSON no webpage my friend ;)
  }else{
    //Serial.println("plain: " + server.arg("plain"));
    DynamicJsonDocument postedJSON(2048);
    deserializeJson(postedJSON,server.arg("plain"));
    String switchId = postedJSON["switchId"];
    String jsonConfig;
    String dataFile = "/switchConfig." + switchId + ".json";
    //Serial.println("Opening " + dataFile);
    File file = SPIFFS.open(dataFile);
    while (file.available()) {
        // Extract each characters by one by one
        jsonConfig = file.readString();
    }
    //Serial.print("JSON Document is: ");
    //Serial.println(jsonConfig);
    if(jsonConfig == "")
    {
      //we need to send a dummy set of values
      String jsonString = "{\"switchId\" : " + switchId + ",\"switchName\":\"undefined\",\"switchDebounce\":\"1000\",\"switchIsFlipper\":\"false\",\"switchIsStart\":\"false\",\"switchIsCredit\":\"false\",\"switchIsOuthole\":\"false\",\"switchDebug\":\"false\"}";
      server.send(200, "text/plain", jsonString ); //Send ADC value only to client ajax request

    }else{
      server.send(200, "text/plain", jsonConfig); //Send ADC value only to client ajax request
    }
    
  }



}
void web_handle_setSwitchConfig()
{
  if(server.args() == 0)
  {
    Serial.println("No JSON in request"); //no JSON no webpage my friend ;)
  }else{
    //Serial.println("SetSwitchConfig: plain: " + server.arg("plain"));
    DynamicJsonDocument postedJSON(2048);
    deserializeJson(postedJSON,server.arg("plain"));
    String switchId = postedJSON["switchId"];
    DynamicJsonDocument myJsonDocument(1024);
    JsonObject jobject = myJsonDocument.to<JsonObject>();
    jobject["switchId"] = postedJSON["switchId"];
    jobject["switchName"] = postedJSON["switchName"];
    jobject["switchDebounce"] = postedJSON["switchDebounce"];
    jobject["switchIsFlipper"] = postedJSON["switchIsFlipper"];
    jobject["switchIsStart"] = postedJSON["switchIsStart"];
    jobject["switchIsCredit"] = postedJSON["switchIsCredit"];
    jobject["switchIsOuthole"] = postedJSON["switchIsOuthole"];
    jobject["switchDebug"] = postedJSON["switchDebug"];
    String dataFile = "/switchConfig." + switchId + ".json";
    const char * dataChar = dataFile.c_str();
    fileSystem.saveToFile(dataChar,postedJSON);
    server.send(200, "text/plain", "{'Status' : 'OK'}"); //Send ADC value only to client ajax request
  }



}
void web_handle_config_switches()
{
// calculate the required buffer size (also accounting for the null terminator):
  int bufferSize = strlen(html_header) + strlen(CONFIG_SWITCHES_page) + strlen(html_footer) + strlen(switchConfig_script_footer) + 1;

  // allocate enough memory for the concatenated string:
  char* concatString = new char[ bufferSize ];

  // copy strings one and two over to the new buffer:
  strcpy( concatString, html_header );
  strcat( concatString, CONFIG_SWITCHES_page );
  strcat( concatString, html_footer );
  strcat( concatString, switchConfig_script_footer );

  server.send(200, "text/html", concatString); //Send web page
  delete[] concatString;
 
}


void web_handle_getCoilConfig()
{
  if(server.args() == 0)
  {
    Serial.println("No JSON in request"); //no JSON no webpage my friend ;)
  }else{
    //Serial.println("plain: " + server.arg("plain"));
    DynamicJsonDocument postedJSON(2048);
    deserializeJson(postedJSON,server.arg("plain"));
    String coilId = postedJSON["coilId"];
    String jsonConfig;
    String dataFile = "/coilConfig." + coilId + ".json";
    //Serial.println("Opening " + dataFile);
    File file = SPIFFS.open(dataFile);
    while (file.available()) {
        // Extract each characters by one by one
        jsonConfig = file.readString();
    }
    //Serial.print("JSON Document is: ");
    //Serial.println(jsonConfig);
    if(jsonConfig == "")
    {
      //we need to send a dummy set of values
      String jsonString = "{\"coilId\" : " + coilId + ",\"coilName\":\"undefined\",\"shiftRegister\":\"\",\"shiftRegisterBit\":\"\",\"pulseTime\":\"50\",\"pulseBackOff\":\"500\"}";
      server.send(200, "text/plain", jsonString ); //Send ADC value only to client ajax request

    }else{
      server.send(200, "text/plain", jsonConfig); //Send ADC value only to client ajax request
    }
    
  }



}
void web_handle_setCoilConfig()
{
  if(server.args() == 0)
  {
    Serial.println("No JSON in request"); //no JSON no webpage my friend ;)
  }else{
    //Serial.println("SetCoilConfig: plain: " + server.arg("plain"));
    DynamicJsonDocument postedJSON(2048);
    deserializeJson(postedJSON,server.arg("plain"));
    String coilId = postedJSON["coilId"];
    DynamicJsonDocument myJsonDocument(1024);
    JsonObject jobject = myJsonDocument.to<JsonObject>();
    jobject["coilId"] = postedJSON["coilId"];
    jobject["coilName"] = postedJSON["coilName"];
    jobject["shiftRegister"] = postedJSON["shiftRegister"];
    jobject["shiftRegisterBit"] = postedJSON["shiftRegisterBit"];
    jobject["pulseTime"] = postedJSON["pulseTime"];
    jobject["pulseBackOff"] = postedJSON["pulseBackOff"];
    String dataFile = "/coilConfig." + coilId + ".json";
    const char * dataChar = dataFile.c_str();
    fileSystem.saveToFile(dataChar,postedJSON);
    server.send(200, "text/plain", "{'Status' : 'OK'}"); //Send ADC value only to client ajax request
  }



}
void web_handle_config_coils()
{
// calculate the required buffer size (also accounting for the null terminator):
  int bufferSize = strlen(html_header) + strlen(CONFIG_COILS_page) + strlen(html_footer) + strlen(coilConfig_script_footer) + 1;

  // allocate enough memory for the concatenated string:
  char* concatString = new char[ bufferSize ];

  // copy strings one and two over to the new buffer:
  strcpy( concatString, html_header );
  strcat( concatString, CONFIG_COILS_page );
  strcat( concatString, html_footer );
  strcat( concatString, coilConfig_script_footer );

  server.send(200, "text/html", concatString); //Send web page
  delete[] concatString;
 
}

void web_handle_getswitchcoilbindingConfig()
{
  if(server.args() == 0)
  {
    Serial.println("No JSON in request"); //no JSON no webpage my friend ;)
  }else{
    //Serial.println("plain: " + server.arg("plain"));
    DynamicJsonDocument postedJSON(2048);
    deserializeJson(postedJSON,server.arg("plain"));
    String switchId = postedJSON["switchId"];
    String jsonConfig;
    String dataFile = "/switchCoilBindingConf." + switchId + ".json";
    //Serial.println("Opening " + dataFile);
    File file = SPIFFS.open(dataFile);
    while (file.available()) {
        // Extract each characters by one by one
        jsonConfig = file.readString();
    }
    //Serial.print("JSON Document is: ");
    //Serial.println(jsonConfig);
    if(jsonConfig == "")
    {
      //we need to send a dummy set of values
      String jsonString = "{\"switchId\" : " + switchId + ",\"coilBinding\":\"-1\",\"instantCoilFire\":\"false\"}";
      server.send(200, "text/plain", jsonString ); //Send ADC value only to client ajax request

    }else{
      server.send(200, "text/plain", jsonConfig); //Send ADC value only to client ajax request
    }
    
  }



}
void web_handle_setswitchcoilbindingConfig()
{
  if(server.args() == 0)
  {
    Serial.println("No JSON in request"); //no JSON no webpage my friend ;)
  }else{
    Serial.println("SetSwitchConfig: plain: " + server.arg("plain"));
    DynamicJsonDocument postedJSON(2048);
    deserializeJson(postedJSON,server.arg("plain"));
    String switchId = postedJSON["switchId"];
    DynamicJsonDocument myJsonDocument(1024);
    JsonObject jobject = myJsonDocument.to<JsonObject>();
    jobject["switchId"] = postedJSON["switchId"];
    jobject["coilBinding"] = postedJSON["coilBinding"];
    jobject["instantCoilFire"] = postedJSON["instantCoilFire"];
   
    String dataFile = "/switchCoilBindingConf." + switchId + ".json";
    const char * dataChar = dataFile.c_str();
    fileSystem.saveToFile(dataChar,postedJSON);
    server.send(200, "text/plain", "{'Status' : 'OK'}"); //Send ADC value only to client ajax request
  }



}
void web_handle_config_switchcoilbinding()
{
// calculate the required buffer size (also accounting for the null terminator):
  int bufferSize = strlen(html_header) + strlen(CONFIG_SWITCHCOILBINDING_page) + strlen(html_footer) + strlen(switchCoilBindingConfig_script_footer) + 1;

  // allocate enough memory for the concatenated string:
  char* concatString = new char[ bufferSize ];

  // copy strings one and two over to the new buffer:
  strcpy( concatString, html_header );
  strcat( concatString, CONFIG_SWITCHCOILBINDING_page );
  strcat( concatString, html_footer );
  strcat( concatString, switchCoilBindingConfig_script_footer );

  server.send(200, "text/html", concatString); //Send web page
  delete[] concatString;
 
}

void web_handle_getlightingConfig()
{
}
void web_handle_setlightingConfig()
{
}

void web_handle_gettitlesConfig()
{
}
void web_handle_settitlesConfig()
{
}

void web_handle_getcreditsConfig()
{
}
void web_handle_setcreditsConfig()
{
}

void web_handle_getinstructionsConfig()
{
}
void web_handle_setinstructionsConfig()
{
}

void web_handle_getmodesConfig()
{
}
void web_handle_setmodesConfig()
{
}


void web_handle_config_()
{
// calculate the required buffer size (also accounting for the null terminator):
  int bufferSize = strlen(html_header) + strlen(CONFIG_DUMMY_page) + strlen(html_footer) + strlen(dummy_script_footer) + 1;

  // allocate enough memory for the concatenated string:
  char* concatString = new char[ bufferSize ];

  // copy strings one and two over to the new buffer:
  strcpy( concatString, html_header );
  strcat( concatString, CONFIG_DUMMY_page );
  strcat( concatString, html_footer );
  strcat( concatString, dummy_script_footer );

  server.send(200, "text/html", concatString); //Send web page
  delete[] concatString;
 
}

void web_handle_config_menu()
{
// calculate the required buffer size (also accounting for the null terminator):
  int bufferSize = strlen(html_header) + strlen(CONFIG_MENU_page) + strlen(html_footer) + strlen(dummy_script_footer) + 1;

  // allocate enough memory for the concatenated string:
  char* concatString = new char[ bufferSize ];

  // copy strings one and two over to the new buffer:
  strcpy( concatString, html_header );
  strcat( concatString, CONFIG_MENU_page );
  strcat( concatString, html_footer );
  strcat( concatString, dummy_script_footer );

  server.send(200, "text/html", concatString); //Send web page
  delete[] concatString;
 
}

void web_handle_config_lighting()
{
// calculate the required buffer size (also accounting for the null terminator):
  int bufferSize = strlen(html_header) + strlen(CONFIG_DUMMY_page) + strlen(html_footer) + strlen(dummy_script_footer) + 1;

  // allocate enough memory for the concatenated string:
  char* concatString = new char[ bufferSize ];

  // copy strings one and two over to the new buffer:
  strcpy( concatString, html_header );
  strcat( concatString, CONFIG_DUMMY_page );
  strcat( concatString, html_footer );
  strcat( concatString, dummy_script_footer );

  server.send(200, "text/html", concatString); //Send web page
  delete[] concatString;
 
}

void web_handle_config_titles()
{
// calculate the required buffer size (also accounting for the null terminator):
  int bufferSize = strlen(html_header) + strlen(CONFIG_DUMMY_page) + strlen(html_footer) + strlen(dummy_script_footer) + 1;

  // allocate enough memory for the concatenated string:
  char* concatString = new char[ bufferSize ];

  // copy strings one and two over to the new buffer:
  strcpy( concatString, html_header );
  strcat( concatString, CONFIG_DUMMY_page );
  strcat( concatString, html_footer );
  strcat( concatString, dummy_script_footer );

  server.send(200, "text/html", concatString); //Send web page
  delete[] concatString;
 
}

void web_handle_config_credits()
{
// calculate the required buffer size (also accounting for the null terminator):
  int bufferSize = strlen(html_header) + strlen(CONFIG_DUMMY_page) + strlen(html_footer) + strlen(dummy_script_footer) + 1;

  // allocate enough memory for the concatenated string:
  char* concatString = new char[ bufferSize ];

  // copy strings one and two over to the new buffer:
  strcpy( concatString, html_header );
  strcat( concatString, CONFIG_DUMMY_page );
  strcat( concatString, html_footer );
  strcat( concatString, dummy_script_footer );

  server.send(200, "text/html", concatString); //Send web page
  delete[] concatString;
 
}

void web_handle_config_instructions()
{
// calculate the required buffer size (also accounting for the null terminator):
  int bufferSize = strlen(html_header) + strlen(CONFIG_DUMMY_page) + strlen(html_footer) + strlen(dummy_script_footer) + 1;

  // allocate enough memory for the concatenated string:
  char* concatString = new char[ bufferSize ];

  // copy strings one and two over to the new buffer:
  strcpy( concatString, html_header );
  strcat( concatString, CONFIG_DUMMY_page );
  strcat( concatString, html_footer );
  strcat( concatString, dummy_script_footer );

  server.send(200, "text/html", concatString); //Send web page
  delete[] concatString;
 
}

void web_handle_config_modes()
{
// calculate the required buffer size (also accounting for the null terminator):
  int bufferSize = strlen(html_header) + strlen(CONFIG_DUMMY_page) + strlen(html_footer) + strlen(dummy_script_footer) + 1;

  // allocate enough memory for the concatenated string:
  char* concatString = new char[ bufferSize ];

  // copy strings one and two over to the new buffer:
  strcpy( concatString, html_header );
  strcat( concatString, CONFIG_DUMMY_page );
  strcat( concatString, html_footer );
  strcat( concatString, dummy_script_footer );

  server.send(200, "text/html", concatString); //Send web page
  delete[] concatString;
 
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
  setting_osr1latchPin = postedJSON["osr1latchPin"];
  setting_osr1clockPin = postedJSON["osr1clockPin"];
  setting_osr1dataPin = postedJSON["osr1dataPin"];
  setting_osr2latchPin = postedJSON["osr2latchPin"];
  setting_osr2clockPin = postedJSON["osr2clockPin"];
  setting_osr2dataPin = postedJSON["osr2dataPin"];
  setting_osr3latchPin = postedJSON["osr3latchPin"];
  setting_osr3clockPin = postedJSON["osr3clockPin"];
  setting_osr3dataPin = postedJSON["osr3dataPin"];
  setting_isrload = postedJSON["isrload"];
  setting_isrclockEnablePin = postedJSON["isrclockEnablePin"];
  setting_isrdataIn = postedJSON["isrdataIn"];
  setting_isrclockIn = postedJSON["isrclockIn"];
  setting_hvrPin = postedJSON["hvrPin"];
  setting_flipper1Pin = postedJSON["flipper1Pin"];
  setting_flipper2Pin = postedJSON["flipper2Pin"];
  setting_switchMatrixRows = postedJSON["switchMatrixRows"];
  setting_switchMatrixColumns = postedJSON["switchMatrixColumns"];

  updateConfigFiles();
  web_handle_action_restart();
  return true;
}


void web_handle_config()
{
// calculate the required buffer size (also accounting for the null terminator):
  int bufferSize = strlen(html_header) + strlen(CONFIG_page) + strlen(html_footer) + strlen(config_script_footer) + 1;

  // allocate enough memory for the concatenated string:
  char* concatString = new char[ bufferSize ];

  // copy strings one and two over to the new buffer:
  strcpy( concatString, html_header );
  strcat( concatString, CONFIG_page );
  strcat( concatString, html_footer );
  strcat( concatString, config_script_footer );

  server.send(200, "text/html", concatString); //Send web page
  delete[] concatString;
 
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

void web_handle_configDownload()
{
    // calculate the required buffer size (also accounting for the null terminator):
  int bufferSize = strlen(html_header) + strlen(DOWNLOAD_page) + strlen(html_footer) + strlen(download_script_footer) + 1;

  // allocate enough memory for the concatenated string:
  char* concatString = new char[ bufferSize ];

  // copy strings one and two over to the new buffer:
  strcpy( concatString, html_header );
  strcat( concatString, DOWNLOAD_page );
  strcat( concatString, html_footer );
  strcat( concatString, download_script_footer );

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

void web_handle_listFS()
{
  //get all files on spiffs and list back as a JSON
  //SerialListDir(SPIFFS, "/");

  //count number of files
  int fileCount = CountConfigFiles(SPIFFS, "/");
  Serial.println("Listing "+(String)fileCount+" files");
  DynamicJsonDocument myJsonDocument(4096);
  JsonObject jobject = myJsonDocument.to<JsonObject>();
  for(int x = 0; x < fileCount; x++)
  {
    String jobjectKey = "value"+(String)x;
    String jobjectValue = getFileNameByNumber(SPIFFS, "/", x);
    //Serial.println("Adding item " + (String)x + "to the JSON -  key is " + jobjectKey + " value is " + jobjectValue);
    jobject[jobjectKey] = jobjectValue;

  }
  
  String jsonString;
  serializeJson(jobject, jsonString);
  server.send(200, "text/html", jsonString);
}

void web_handle_getFS(){
  //Serial.print("Number of Arguments recieved is ");
  //Serial.println(server.args());
  String dataFile ="NULL";
  String jsonConfig;
  String jsonString = "{\"null\":\"null\"}";
  if(server.args() == 1)
  {
    dataFile = server.arg(0);
     
    //need to return the JSON file
    File file = SPIFFS.open("/"+dataFile);
    while (file.available()) {
        // Extract each characters by one by one
        jsonConfig = file.readString();
    }
    if(jsonConfig == "")
    {
      //we need to send a dummy set of values
      
      server.send(200, "text/plain", jsonString ); //Send ADC value only to client ajax request

    }else{
      server.send(200, "application/octet-stream", jsonConfig); //Send ADC value only to client ajax request
    }

  }else{
    server.send(200, "text/plain", jsonString ); //Send ADC value only to client ajax request
  }

}

/* END web page functions */

