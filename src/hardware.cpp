#include "hardware.h"

String relay_state = "off";

void hardware_setup(){
    pinMode(relay_engine_pin, OUTPUT);
    digitalWrite(relay_engine_pin, LOW);

    pinMode(relay_parachute_pin, OUTPUT);
    digitalWrite(relay_parachute_pin, LOW);
}