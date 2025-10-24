#pragma once
#include <WiFi.h>
#include <Arduino.h>


extern IPAddress IP;
extern String header;
extern WiFiServer server;


extern unsigned long clicked_time; 

void setup_wifi();
void Print_client(WiFiClient client);

