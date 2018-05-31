/*
 Name:		EnhancedSerial.cpp
 Created:	13-Feb-18 12:34:38 PM
 Author:	ekampourakis
*/

#include "EnhancedSerial.h"

byte DeviceID;
byte LED;
bool Status = false;
byte PingBytes[2] = { 0xFF };
byte RX[2] = { 0x00 };
long CurrentBaud = 9600;

void EnhancedSerial::Init(byte ID) {
	DeviceID = ID;
	Serial.begin(CurrentBaud);
}

void EnhancedSerial::Init(byte ID, byte LEDPin) {
	DeviceID = ID;
	Serial.begin(CurrentBaud);
	LED = LEDPin;
	pinMode(LED, OUTPUT);
	digitalWrite(LED, LOW);
}

bool EnhancedSerial::IsConnected() { return Status; }

void EnhancedSerial::SetPingMessage(byte One, byte Two) {
	PingBytes[0] = One;
	PingBytes[1] = Two;
}

void EnhancedSerial::SetTimeout(long Milliseconds) {
	Serial.setTimeout(Milliseconds);
}

long EnhancedSerial::BaudFromSerial(byte BaudCode) {
	switch (BaudCode) {
		case 0:
			return 1200;
		case 1:
			return 2400;
		case 2:
			return 4800;
		case 3:
			return 9600;
		case 4:
			return 14400;
		case 5:
			return 19200;
		case 6:
			return 28800;
		case 7:
			return 38400;
		case 8:
			return 57600;
		case 9:
			return 76800;
		case 10:
			return 115200;
		case 11:
			return 230400;
		case 12:
			return 250000;
		case 13:
			return 500000;
		case 14:
			return 1000000;
		default:
			return 9600;
	}
}

long EnhancedSerial::GetBaud() { return CurrentBaud; }

bool EnhancedSerial::Pinged() { return (RX[0] == PingBytes[0] && RX[1] == PingBytes[1]); }

void EnhancedSerial::FlushAll() {
	Serial.flush();
	while (Serial.available()) { Serial.read(); }
}

int EnhancedSerial::PingReceived() {
	if (Serial.available()) {
		RX[0] = RX[1];
		int ReceivedByte = Serial.read();
		if (ReceivedByte == -1) {
			return -2;
		}
		RX[1] = Serial.read();
		return Pinged() ? -1 : RX[1];
	} 
	return -2;
}

void EnhancedSerial::PingBack() {
	Serial.write(PingBytes, 2);
	Serial.flush();
}

// Add timeout
void EnhancedSerial::PingRead() {
	if (Serial.available()) {
		RX[0] = RX[1];
		RX[1] = Serial.read();
		if (Pinged()) {
			if (LED != -1) { digitalWrite(LED, LOW); }
			delay(100);
			FlushAll();
			Serial.write(DeviceID);
			Status = true;
			long RequestedBaud = -1;
			while (RequestedBaud == -1) {
				if (Serial.available() > 0) {
					RequestedBaud = Serial.read();
				}	
			}
			FlushAll();
			CurrentBaud = BaudFromSerial(RequestedBaud);
			Serial.begin(CurrentBaud);
			Status = true;
			if (LED != -1) { digitalWrite(LED, HIGH); }
		}
	}
}

void EnhancedSerial::TryConnect() {
	if (!Status) {
		PingRead();
	}
}

void EnhancedSerial::WaitConnect() {
	while (!Status) {
		PingRead();
	}
}