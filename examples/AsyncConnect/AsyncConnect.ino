#include <EnhancedSerial.h>

EnhancedSerial ES;

void setup() {
	
  //Initialize ES with an unique ID
  ES.Init(0xB8);
  
}

void loop() {
  
  //Try to connect asynchronously
  //This needs to be called frequently 
  //If ES is connected it won't do anything
  ES.TryConnect();

  if (ES.IsConnected()) {
	  
    //You can call Serial methods as usual
	
  } else {
	  
    //As ES hasn't yet established a connection
    //with the host, it's better to avoid calling
    //any Serial methods until it connects
	
  }
  
}