#include <EnhancedSerial.h>

EnhancedSerial ES;

#define LEDPin 6

void setup() {
	
  // Initialize ES with the default unique ID
  ES.Init(13);
  
  // Change the unique ping message (default is 255 and 255)
  ES.SetPingMessage(0, 255);
  
  // Wait until ES connects to the host
  ES.WaitConnect();
  
  // You won't need to call Serial.begin() as EnhancedSerial initializes
  // the Serial internally with the Baud rate specified by the host application
  
  // Set the pin of the LED as output and turn it off
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, LOW);
}

void loop() {

  // This will check the next available byte in the Serial buffer for matching ping message
  // Be careful as this will result in loss of incoming bytes if not handled correctly
  // To solve the data loss -1 is returned when ping pattern matches
  // If the ping pattern does not match then the received byte will be returned
  // If no data is available or the read timed out then -2 will be returned
  int RX = ES.PingReceived();
  if (RX == -1) {
	// Ping pattern matches so ping back
	ES.PingBack();
  } else if (RX == -2) {
	// Read timed out or no incoming bytes available
  } else {
	// Ping pattern does not match so turn the LED on or off based on received data
	if (RX == 0) {
	  // If received byte is 0 then turn the LED off
	  digitalWrite(LEDPin, LOW);
	} else {
	  // If received byte is other than 0 then turn the LED on
	  digitalWrite(LEDPin, HIGH);
	}
  }
  
}