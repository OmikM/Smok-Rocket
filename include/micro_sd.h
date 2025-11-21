#pragma once
#include <FS.h>
#include <vector>
#include <Arduino.h>
using namespace std;

void writeFile(fs::FS &fs, const char * path, const char * message);
void readFile(fs::FS &fs, const char * path);
void appendFile(fs::FS &fs, const char * path, const char * message);
void write_log_start(fs::FS &fs);
void save_data_BM(fs::FS &fs);