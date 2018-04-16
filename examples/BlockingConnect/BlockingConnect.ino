#include <EnhancedSerial.h>

EnhancedSerial ES;

void setup() {
	
  // Initialize ES with the default unique ID
  ES.Init(13);
  
  // Change the unique ping message (default is 255 and 255)
  ES.SetPingMessage(0, 255);
  
  // Wait until ES connects to the host
  ES.WaitConnect();
  
  // You won't need to call Serial.begin() as EnhancedSerial initializes
  // the Serial internally with the Baud rate specified by the host application
}

void loop() {
	
  // After initialization and connection you can use Serial functions as usual
  Serial.println("Hello World!");
  delay(1000);
  
}