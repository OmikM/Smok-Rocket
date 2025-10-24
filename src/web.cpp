#include <WiFi.h>
#include "web.h"
#include "BM.h"
#include "hardware.h"
#include "vars.h"

using namespace std;

const char* ssid     = "ESP32-Smok";
const char* password = "123456789";

IPAddress IP;
String header;
WiFiServer server(80); 

void setup_wifi(){
      // Connect to Wi-Fi network with SSID and password
    Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
    WiFi.softAP(ssid, password);

    IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
  
    server.begin();
    relay_state = "off";

}

unsigned long clicked_time;

void Print_client(WiFiClient client){
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
        if (client.available()) {             // if there's bytes to read from the client,
            char c = client.read();             // read a byte, then
            //Serial.write(c);                    // print it out the serial monitor
            header += c;
            if (c == '\n') {                    // if the byte is a newline character
                // if the current line is blank, you got two newline characters in a row.
                // that's the end of the client HTTP request, so send a response:
                if (currentLine.length() == 0) {
                    // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                    // and a content-type so the client knows what's coming, then a blank line:
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-type:text/html");
                    client.println("Connection: close");
                    client.println();

            
                    // turns the GPIOs on and off
                    if (header.indexOf("GET /27/on") >= 0) {
                        if(clicked_time == 0){
                            clicked_time = millis();
                        }
                        

                    } else if (header.indexOf("GET /27/off") >= 0) {
                        clicked_time = 0;
                    }

                    client.println(millis());
                    client.println(clicked_time);
                    Serial.println((millis() - clicked_time)/1000);
            
                    // Display the HTML web page
                    client.println("<!DOCTYPE html><html>");
                    client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                    client.println("<meta http-equiv=\"refresh\" content=\"1\">"); // refresh every 1 second

                    client.println("<link rel=\"icon\" href=\"data:,\">");
                    // CSS to style the on/off buttons 
                    // Feel free to change the background-color and font-size attributes to fit your preferences
                    client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
                    client.println(".button { background-color: #fa0303ff; border: none; color: white; padding: 16px 40px;");
                    client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
                    client.println(".button2 {background-color: #555555;}</style></head>");
            
                    // Web Page Heading
                    client.println("<body><h1>SMOK</h1>");
               
                    // Display current state, and ON/OFF buttons for GPIO 27  
                    client.println("<p>Rozpocznij Odliczanie (10s)" "</p>");
                    // If the output27State is off, it displays the ON button

       
                    if (started!=true) {
                        if(clicked_time>0){
                            client.println("<p><a href=\"/27/off\"><button class=\"button button2\">");
                            client.println(countdown-((millis()-clicked_time)/1000));
                            client.println("</button></a></p>");
                        }else{
                            client.println("<p><a href=\"/27/on\"><button class=\"button\">Start</button></a></p>");
                        }
                    } else {
                        client.println("<p><a href=\"/27/off\"><button class=\"button button2\">Leci!!!</button></a></p>");
                    }

                    client.println("<div><h2>Dane z czujnikow:</h2> <p> B388: <ul> <li>Pressure");
                    client.println(Pressure);
                    client.println("</li> <li> altitude");
                    client.println(Pressure);
                    client.println("</li> <li>temperature");
                    client.println(altitude);

                    client.println("</li> </ul></p></div>");

                    client.println("</body></html>");
            
                    // The HTTP response ends with another blank line
                    client.println();
                    // Break out of the while loop
                    break;
                } else { // if you got a newline, then clear currentLine
                    currentLine = "";
                }
            } else if (c != '\r') {  // if you got anything else but a carriage return character,
                currentLine += c;      // add it to the end of the currentLine
            }
        }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    // Serial.println("Client disconnected.");
    // Serial.println("");
}