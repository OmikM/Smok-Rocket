#include <WiFi.h>
#include "web.h"
#include "hardware.h"
#include "BM.h"
#include "vars.h"

// Variable to store the HTTP request



void setup() {
    Serial.begin(115200);
    delay(5000);
  
    setup_wifi();
	hardware_setup();
  	setup_BM();


}

void start(){
	digitalWrite(relay_engine_pin, HIGH);
	started = true;
	start_time = millis();
}

void para_open(){
	digitalWrite(relay_parachute_pin, HIGH);
	started = true;
	start_time = millis();

	para_opend = true;
}


bool para_con(){
	if((millis()-start_time)/1000<min_time_para){
		return false;
	}

	Serial.println("altitude");
	Serial.println(altitude);
	Serial.println(max_alti);
	Serial.println("DIFF");
	Serial.println(max_alti - altitude);
	Serial.println(alti_diff);

	if(max_alti - altitude > alti_diff){
		return true;
	}

	return false;
}

int i;
void loop(){
	i++;
	update_BM();
    if(i%1000==0){
        Serial.print("AP IP address: ");
        Serial.println(IP);
        i = 0;
		print_BM();
		
    }
	WiFiClient client = server.available();   // Listen for incoming clients

	if (client) {                             // If a new client connects,
    	Serial.println("New Client.");          // print a message out in the serial port
    	Print_client(client);
  	}


	if(clicked_time > 0 and ((millis()-clicked_time)/1000)>countdown and !started){
    	start();
    }

	if(started){
		if(para_con()){
			para_open();
		}
	}

}