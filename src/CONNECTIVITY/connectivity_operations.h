#include <Arduino.h>


void ConnectivityOperationsFunction( void * pvParameters)
{
    //the resolved ip from the DNS query
    IPAddress server_ip_resolved;

    boolean dns_resolved = false;
    boolean http_responded = false;

    //now we loop
    for(;;)
    {

        
        //Serial.println("Connectivity Operations Loop");
        /*HTTPClient http;
        http.begin(HOST_NAME + PATH_NAME); //HTTP
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // file found at server
            if(httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            Serial.println(payload);
            } else {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);
            }
        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
            server.client().flush();
        }

        http.end();*/






        vTaskDelay(pdMS_TO_TICKS(10000)); //yeild

    }
}