#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <Arduino.h>
#include "hardware.h"
#include "micro_sd.h"
#include "string.h"
#include "vars.h"

using namespace std;

//source https://randomnerdtutorials.com/esp32-microsd-card-arduino/



void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file: ");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}


void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
            Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
    file.close();
}

void write_log_start(fs::FS &fs){
    writeFile(SD, "log.txt", "time,temperature,altitude,Pressure \n");

    string row = 
        "Start: \n  Time: " + to_string(millis()) + '\n' + 
        "  temperature: " + to_string(start_temp) + '\n' +  
        "  temperature: " + to_string(start_alti) + '\n' + 
        "  presure: " +to_string(start_pre) + "\n";

    writeFile(SD, "data.txt", row.c_str());
}


void save_data_BM(fs::FS &fs){
    string row = 
    to_string((millis() - start_time)) + ',' + 
    to_string(temperature) + ',' +  
    to_string(altitude-start_alti) + ',' + 
    to_string(Pressure) + "\n";

    appendFile(SD, "log.txt", row.c_str());
}


    // uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    // Serial.printf("SD Card Size: %lluMB\n", cardSize);

    // listDir(SD, "/", 0);
    // createDir(SD, "/mydir");
    // listDir(SD, "/", 0);
    // removeDir(SD, "/mydir");
    // listDir(SD, "/", 2);
    // writeFile(SD, "/hello.txt", "Hello ");
    // appendFile(SD, "/hello.txt", "World!\n");
    // readFile(SD, "/hello.txt");
    // deleteFile(SD, "/foo.txt");
    // renameFile(SD, "/hello.txt", "/foo.txt");
    // readFile(SD, "/foo.txt");
    // testFileIO(SD, "/test.txt");
    // Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
    // Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
