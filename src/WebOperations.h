#include <Arduino.h>
#include <WebServer.h>
#include <Update.h>

#include "web_dashboard.h"
#include "web_upload.h"

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

void web_handle_viewState();
void web_handle_firmwareUpload();

void web_handle_switchDebug();
void web_handle_coilDebug();
void web_handle_opsDebug();


void web_handle_action_startbutton();
void web_handle_action_restart();
void web_handle_action_outholeswitch();
void web_handle_action_rolloverswitch();
void web_handle_action_leftrolloverswitch();
void web_handle_action_rightrolloverswitch();
void web_handle_action_leftflipperswitch();
void web_handle_action_rightflipperswitch();
void web_handle_action_leftslingswitch();
void web_handle_action_rightslingswitch();
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


//setup a task to run on core 0;
TaskHandle_t WebOperationsTask;


void WebOperationsFunction( void * pvParameters)
{
    int counterWeb = 0;
    unsigned long lastMillisWeb = 0;
    //Setup functions
    //Actual Web Pages
    server.on("/viewState", web_handle_viewState);
    server.on("/uploadDev", web_handle_firmwareUpload);

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

    //Toggle the debug messgaes seen on serial
    server.on("/debug/switch", web_handle_switchDebug);
    server.on("/debug/coil", web_handle_coilDebug);
    server.on("/debug/ops", web_handle_opsDebug);
  
    //some virtual buttons to do work 
    server.on("/action/startbutton", web_handle_action_startbutton);
    server.on("/action/outholeswitch", web_handle_action_outholeswitch);
    server.on("/action/rolloverswitch", web_handle_action_rolloverswitch);
    server.on("/action/restart", web_handle_action_restart);    

    server.on("/", web_handle_viewState);
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
    while ((WifiConnected != true) && (WifiWaitCounter < MaxWait)) {
      Serial.println("Webserver Waiting for Wifi");
      vTaskDelay(1000);
      WifiWaitCounter +=1;
    }
    if(WifiConnected == true)
    {
      server.begin();
      Serial.println("Webserver Started");
    }else
    {
      Serial.println("Webserver NOT Started");
      //Lets forget about fifi and webserver
      vTaskDelete(NULL);
    }

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
          Serial.print(counter/10);
          Serial.println("Hz (full program cycles per second)");
        }
      WEBHz = counterWeb/10;  
      counterWeb = 0;
      lastMillisWeb = millis();
    }
    // End of debug stuff 
      //webserver code
    if(WifiConnected ==true)
    {
        server.handleClient();
    }
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
    server.send(200, "text/plane", MachineStateWrite); //Send ADC value only to client ajax request
}
void web_handle_AJAXCPU0Hz()
{
    server.send(200, "text/plane", (String)CMOHz); //Send ADC value only to client ajax request
}
void web_handle_AJAXCPU1Hz()
{
    server.send(200, "text/plane", (String)WEBHz); //Send ADC value only to client ajax request
}
void web_handle_AJAXPlayerNumber()
{
  String PlayerNmuberText = (String)g_myPinballGame.getCurrentPlayerNumber() + " of " + (String)g_myPinballGame.getCurrentPlayerNumbers();
  server.send(200, "text/plane", PlayerNmuberText);
}
void web_handle_AJAXBallNumber()
{
  server.send(200, "text/plane", (String)g_myPinballGame.getCurrentBallNumber(g_myPinballGame.getCurrentPlayerNumber()));
}
void web_handle_AJAXPlayerScore()
{
  server.send(200, "text/plane", (String)g_myPinballGame.getPlayerScore(g_myPinballGame.getCurrentPlayerNumber()));
}
void web_handle_AJAXBallSave()
{
  bool BallSaveActive = g_myPinballGame.isBallSave();
  String BallSaveTextReturn = "OFF";
  if(BallSaveActive == 1)
  {
    BallSaveTextReturn = "ON";
  }
  server.send(200, "text/plane", BallSaveTextReturn);
}
void web_handle_AJAXTopDisplay()
{
  server.send(200, "text/plane", (String)ScoreboardTText);
}
void web_handle_AJAXBottomDisplay()
{
  server.send(200, "text/plane", (String)ScoreboardBText);
}
void web_handle_AJAXP1Score()
{
  server.send(200, "text/plane", (String)g_myPinballGame.getPlayerScore(1));
}
void web_handle_AJAXP2Score()
{
  server.send(200, "text/plane", (String)g_myPinballGame.getPlayerScore(2));
}
void web_handle_AJAXP3Score()
{
  server.send(200, "text/plane", (String)g_myPinballGame.getPlayerScore(3));
}
void web_handle_AJAXP4Score()
{
  server.send(200, "text/plane", (String)g_myPinballGame.getPlayerScore(4));
}
void web_handle_AJAXP1Ball()
{
  server.send(200, "text/plane", (String)g_myPinballGame.getCurrentBallNumber(1));
}
void web_handle_AJAXP2Ball()
{
  server.send(200, "text/plane", (String)g_myPinballGame.getCurrentBallNumber(2));
}
void web_handle_AJAXP3Ball()
{
  server.send(200, "text/plane", (String)g_myPinballGame.getCurrentBallNumber(3));
}
void web_handle_AJAXP4Ball()
{
  server.send(200, "text/plane", (String)g_myPinballGame.getCurrentBallNumber(4));
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
void web_handle_action_leftflipperswitch(){}
void web_handle_action_rightflipperswitch(){}
void web_handle_action_leftslingswitch(){}
void web_handle_action_rightslingswitch(){}
void web_handle_action_leftpopswitch(){}
void web_handle_action_rightpopswitch(){}
void web_handle_action_spinnerswitch(){}
void web_handle_action_leftoutlaneswitch(){}
void web_handle_action_rightoutlaneswitch(){}
void web_handle_action_leftinlaneswitch(){}
void web_handle_action_rightinlaneswitch(){}
void web_handle_action_lefttoplaneswitch(){}
void web_handle_action_righttoplaneswitch(){}
void web_handle_action_centertoplaneswitch(){}
void web_handle_action_saucerswitch(){}
void web_handle_action_standup1switch(){}
void web_handle_action_standup2switch(){}
void web_handle_action_standup3switch(){}
void web_handle_action_standup4switch(){}
void web_handle_action_standup5switch(){}
void web_handle_action_drop1switch(){}
void web_handle_action_drop2switch(){}
void web_handle_action_drop3switch(){}
void web_handle_action_drop4switch(){}
void web_handle_action_drop5switch(){}



void web_handle_action_restart()
{
    ESP.restart();
 
}
/* Page Calls*/
void web_handle_viewState()
{
    String s = MAIN_page; //Read HTML contents
    server.send(200, "text/html", s); //Send web page
 
}
void web_handle_firmwareUpload()
{
  String s = UPLOAD_page; //Read HTML contents
  server.send(200, "text/html", s); //Send web page
}
/* END web page functions */

