/*
Project: ESP32 development board, LEDs
Function: Control of LEDs with Web Server
http://acoptex.com
 */
#include <WiFi.h>//We include the WiFi library

//You need to replace with your network credentials
const char* ssid     = "YOUR_LOCAL_NETWORK_SSID";
const char* password = "YOUR_LOCAL_NETWORK_PASSWORD";

int const gpio26 = 26; //green LED attached to GPIO 26 pin of ESP32 development board
int const gpio27 = 27; //red LED attached to GPIO 27 pin of ESP32 development board

WiFiServer server(80); //We set web server port number
String header;//We create the string variable to store the HTTP request

//We create variables to store the current output state
String gpio26State = "OFF";
String gpio27State = "OFF";

//Other variables
unsigned long currentTime = millis();
unsigned long previousTime = 0; 

const long timeoutTime =2000; //timeout time in milliseconds (2 seconds) 

void setup() {
  Serial.begin(115200); //Initialise serial communication at 115200 bps
  pinMode(gpio26, OUTPUT);//We set gpio 26 pin as OUTPUT
  pinMode(gpio27, OUTPUT);//We set gpio 27 pin as OUTPUT
  digitalWrite(gpio26, LOW);//We set gpio 26 pin to LOW by default
  digitalWrite(gpio27, LOW);//We set gpio 27 pin to LOW by default

  //We connect to local WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //We print in Serial Monitor ESP32 development board IP address
  Serial.println("");
  Serial.println("");
  Serial.println("Connected to local WiFi network.");
  Serial.println("");
  Serial.println("Your ESP32 development board IP address: ");
  Serial.println(WiFi.localIP());
  
  server.begin();//We start the web server
}

void loop(){
  WiFiClient client = server.available();   //We listen for incoming clients

  if (client) {                             //If a new client connects,
    Serial.println("New Client connected.");//We print a message out in the Serial Monitor
    String currentLine = "";                //We make a String variable to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { //We have loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             //If there are bytes to read from the client,
        char c = client.read();             //Read a byte, then
        Serial.write(c);                    //Print it out the Serial Monitor
        header += c;
        if (c == '\n') {                    //If the byte is a newline character
                                            //If the current line is blank, you got two newline characters in a row.
                                            //That's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
                                            
            
            
            client.println("HTTP/1.1 200 OK");       //HTTP headers always start with a response code
            client.println("Content-type:text/html");//and a content-type so the client knows what's coming, 
            client.println("Connection: close");
            client.println();                        //then a blank line
            
                                                    
            if (header.indexOf("GET /greenLED/ON") >= 0) { //turns the LEDs ON/OFF
              Serial.println("Green LED is ON");
              gpio26State = "ON";
              digitalWrite(gpio26, HIGH);
            } else if (header.indexOf("GET /greenLED/OFF") >= 0) {
              Serial.println("Green LED is OFF");
              gpio26State = "OFF";
              digitalWrite(gpio26, LOW);
            } else if (header.indexOf("GET /redLED/ON") >= 0) {
              Serial.println("Red LED is ON");
              gpio27State = "ON";
              digitalWrite(gpio27, HIGH);
            } else if (header.indexOf("GET /redLED/OFF") >= 0) {
              Serial.println("Red LED is OFF");
              gpio27State = "OFF";
              digitalWrite(gpio27, LOW);
            }            
            //We make the HTML web page
            client.println("<!DOCTYPE html><html>"); 
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            //CSS style for ON/OFF buttons 
            //You can change the background-color, font-size, make border, change font color if you want so
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #2E7C4F; border: none; color: white; padding: 16px 40px;");  //ON button CSS style
            client.println("text-decoration: none; font-size: 30px; margin: 2px;}");
            client.println(".button1 {background-color: #FF4C4F; border: none; color: white; padding: 16px 33px;");  //OFF button CSS style
            client.println("text-decoration: none; font-size: 30px; margin: 2px;}</style></head>"); 
            client.println("<body><h1>ESP32 Web Server</h1>");                                                        //Web page heading
            client.println("<p>Green LED is " + gpio26State + "</p>");                                                //We show the current state, ON/OFF buttons for green LED                 
            if (gpio26State=="ON") {                                                                                  //If the gpio26State is OFF, it displays the ON button 
              client.println("<p><a href=\"/greenLED/OFF\"><button class=\"button1\">OFF</button></a></p>");
            } else {              
              client.println("<p><a href=\"/greenLED/ON\"><button class=\"button\">ON</button></a></p>");
            } 
            client.println("<p>Red LED is " + gpio27State + "</p>");                                                  //We show the current state, ON/OFF buttons for red LED 
                  
            if (gpio27State=="ON") {                                                                                  //If the gpio27State is OFF, it displays the ON button 
              client.println("<p><a href=\"/redLED/OFF\"><button class=\"button1\">OFF</button></a></p>");
            } else {
              client.println("<p><a href=\"/redLED/ON\"><button class=\"button\">ON</button></a></p>");
            }
            client.println("</body></html>");       
            client.println();              //We add the blank line on the end of the HTTP response
            
            break;                         //We break out of the while loop
          } else {                         //If you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {            //If you got anything else but a carriage return character,
          currentLine += c;                //add it to the end of the currentLine
        }
      }
    }
    
    header = "";                           //We clear the header variable
    client.stop();                         //We close the connection
    Serial.println("Client disconnected.");//We print the message in Serial Monitor
    Serial.println();
  }
}
