#pragma once

// parashut opening conditions  
// s
const int min_time_para = 2;
//m
const float alti_diff = 0.5;
const int time_igniter = 200;

const int countdown = 5;

extern float start_alti;
extern float start_pre;
extern float start_temp;

extern bool started;
extern unsigned long start_time;

extern float temperature;
extern float Pressure;
extern float altitude;


extern bool para_opend;