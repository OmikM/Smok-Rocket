#pragma once
#include <FS.h>
#include <vector>
#include <Arduino.h>
using namespace std;

void writeFile(const char * path, const char * message);
void readFile(const char * path);
void appendFile(const char * path, const char * message);
void write_log_start();
void save_data_BM();