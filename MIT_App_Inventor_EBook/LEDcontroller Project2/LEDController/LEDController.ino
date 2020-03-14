/*
Project: LED Controller 
Function: We are going to control red LED attached to the digital pin 10 of Arduino Uno via Bluetooth
          through the Android App (made with MIT APP inventor 2)
Credits: ACOPTEX.COM http://acoptex.com
 */
 
int ledPin = 10;//red LED attached to Arduino pin 10 
int state;

void setup() {              
  Serial.begin(9600);   // initialize serial communication at 9600 bps
  pinMode(ledPin, OUTPUT); // set the LED digital pin as an Output.    
  
}

void loop() {
  
  if(Serial.available() > 0){     
      state = Serial.read();}

  if (state == '1') {
      digitalWrite(ledPin, HIGH);}   // turn the red LED ON (The voltage level is HIGH)
 
  else if (state == '0') {
      digitalWrite(ledPin, LOW);}    // turn the LED OFF (The voltage level is LOW)
      
  delay(100);                     // wait for 100ms
  
}
