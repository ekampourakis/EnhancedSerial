/*
 Name:		EnhancedSerial.h
 Created:	13-Feb-18 12:34:38 PM
 Author:	ekampourakis
*/

#ifndef _EnhancedSerial_h
#define _EnhancedSerial_h
#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#endif

class EnhancedSerial {
	public:
		void Init(byte ID);
		void Init(byte ID, byte LEDPin);
		bool IsConnected();
		void SetPingMessage(byte One, byte Two);
		void SetTimeout(long Milliseconds);
		bool TryConnect();
		void WaitConnect();
		long GetBaud();
		
	private:
		void FlushAll();
		bool Pinged();
		void PingRead();
		long BaudFromSerial(byte BaudCode);
};