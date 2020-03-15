/*
  Project: LED Slider
  Function: We are going to control the brightness of red LED attached to the digital pin 10 of Arduino Uno via Bluetooth
            through the Android App (made with MIT APP inventor 2)
  Credits: ACOPTEX.COM http://acoptex.com
*/
const int ledPin = 10;        // red LED attached to Arduino pin 10
int valueLed = 0;             // define value for the LED brightness
boolean debug = true;
void setup() {
  Serial.begin(9600);         // initialize serial communication at 9600 bps
  pinMode(ledPin, OUTPUT);    // set the LED digital pin as an Output.

}

void loop() {

  if (Serial.available() > 0) {           // confirm if bluetooth are available
    while (Serial.available())            // while it is, parse integer numbers.
    {
      valueLed = Serial.parseInt();
      if (debug) {                        // debug it into Arduino IDE Serial Monitor
        Serial.print("Brightness value: ");      // disable it if you will: set boolean debug to false
        Serial.println(valueLed);
      }
      if (Serial.read() == '\n') {analogWrite(ledPin, valueLed);} //Finally send it to Bluetooth port
    }
    delay(100);                         // wait for 100ms
  }
}
