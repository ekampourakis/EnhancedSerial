#include <EnhancedSerial.h>

EnhancedSerial ES;

void setup() {
	
  // Initialize ES with the default unique ID
  ES.Init(13);
  
  // Change the unique ping message (default is 255 and 255)
  ES.SetPingMessage(0, 255);
  
}

void loop() {
  
  // Try to connect asynchronously
  // This needs to be called frequently 
  // If ES is connected it will be bypassed
  ES.TryConnect();

  if (ES.IsConnected()) {
	  
    // You can call Serial methods as usual
	Serial.println("Hello World!");
	delay(1000);
	
  } else {
	  
    // As ES hasn't yet established a connection
    // with the host, it's better to avoid calling
    // any Serial methods until it connects.
	// But you can do other crucial stuff here
	
  }
  
}
