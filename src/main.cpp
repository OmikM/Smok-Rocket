#include <WiFi.h>
#include "web.h"
#include "hardware.h"
#include "BM.h"
#include "vars.h"
#include "micro_sd.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"

// Variable to store the HTTP request



void setup() {
    Serial.begin(115200);
    delay(5000);
  
    setup_wifi();
	hardware_setup();
	digitalWrite(relay_engine_pin, LOW);

  	// setup_BM();


  	// if(!SD.begin(5)){
	//     Serial.println("Card Mount Failed");
	//     return;
  	// }

  	// uint8_t cardType = SD.cardType();

  	// if(cardType == CARD_NONE){
    // 	Serial.println("No SD card attached");
    // 	return;
  	// }
}

void start(){
	digitalWrite(relay_engine_pin, HIGH);
	started = true;
	start_time = millis();
	start_temp = temperature;
	start_pre = Pressure;
	start_alti = altitude;
	write_log_start(SD);
}

void para_open(){
	digitalWrite(relay_parachute_pin, HIGH);

	para_opend = true;
}

//conditons to launch
bool para_con(){
	if((millis()-start_time)/1000<min_time_para){
		return false;
	}

	if(max_alti - altitude > alti_diff){
		Serial.print("altitude: ");
		Serial.println(altitude);
		Serial.print("Max altitude: ");
		Serial.println(max_alti);
		Serial.print("DIFF : ");
		Serial.println(max_alti - altitude);
		Serial.print("alti diff: ");
		Serial.println(alti_diff);
		return true;
	}

	return false;
}

int i;
long long last_save_time = 0;

void loop(){
	i++;
	//update_BM();
    if(i%1000==0){
        Serial.print("AP IP address: ");
        Serial.println(IP);
        i = 0;
		// print_BM();
    }

	// if(millis() - last_save_time > 100 and started){
	// 	last_save_time = millis();
	// 	// save_data_BM(SD);
	// }
	
	WiFiClient client = server.available();   // Listen for incoming clients

	if (client) {                             // If a new client connects,
    	Serial.println("New Client.");          // print a message out in the serial port
    	Print_client(client);
  	}


	if(clicked_time > 0 and ((millis()-clicked_time)/1000)>countdown and !started){
    	start();
    }

	// if(started){
	// 	if(para_opend == false){
	// 		if(para_con()){
	// 			para_open();
	// 		}
	// 	}
	// }

}