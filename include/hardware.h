#pragma once
#include <Arduino.h>
#include <string>
using namespace std;



extern String relay_state;
const int relay_engine_pin = 27;
const int relay_parachute_pin = 14;
const int sd_pin = 13;



void hardware_setup();
