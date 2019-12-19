/*
Alexander Chukhryaev
Arduino Step By Step For Beginners
http://acoptex.com
This example code is in the public domain.
modified 8 May 2014
by Scott Fitzgerald
*/

void setup() {
  //Put your setup code here, to run once:  
  pinMode(13, OUTPUT);//Set the digital pin 13 as an OUTPUT.
}

void loop() {
  //Put your main code here, to run repeatedly:
  digitalWrite(13, HIGH);   //Switch the LED ON
  delay(1000);              //Delay set for a 1000 ms (1 second)
  digitalWrite(13, LOW);    //Switch the LED OFF
  delay(1000);              //Delay set for a 1000 ms (1 second)
}
