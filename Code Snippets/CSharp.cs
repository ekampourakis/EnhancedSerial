// ******* Usage *******
// 
// When main form loads
//
// // serialPort1 is the serial port component used in the program
// // COM7 is the port the Arduino is connected to
// InitSerial(ref serialPort1, "COM7");
//
// On connect button click
//
// byte[] Ping = { 255, 255 }; // is the default ping message used and can be changed from the Arduino code calling SetPingMessage
// // 13 is the device ID used in the sample sketch and can be changed from the Arduino code
// // 115200 is the required baud rate. Change it to any baud rate supported
// ConnectSerial(ref serialPort1, 13, Ping, 115200);
//
// If you want to change baud rate
//
// EndSerial(ref serialPort1);
// byte[] Ping = { 255, 255 };
// ConnectSerial(ref serialPort1, 13, Ping, NewBaudRate);

private byte BaudToCode(int Baud) {
	switch (Baud) {
		case 1200:
			return 0;
		case 2400:
			return 1;
		case 4800:
			return 2;
		case 9600:
			return 3;
		case 14400:
			return 4;
		case 19200:
			return 5;
		case 28800:
			return 6;
		case 38400:
			return 7;
		case 57600:
			return 8;
		case 76800:
			return 9;
		case 115200:
			return 10;
		case 230400:
			return 11;
		case 250000:
			return 12;
		case 500000:
			return 13;
	}
	return 3;
}

bool ConnectionStatus = false;

private void InitSerial(ref System.IO.Ports.SerialPort EnhancedPort, string COMPort) {
	EnhancedPort.DtrEnable = true;
	EnhancedPort.BaudRate = 9600;
	EnhancedPort.PortName = COMPort;
	EnhancedPort.Open();
	while ((EnhancedPort.BytesToRead > 0)) {
		EnhancedPort.ReadByte();
	}
}

private void ConnectSerial(ref System.IO.Ports.SerialPort EnhancedPort, byte DeviceID, byte[] PingMessage, int BaudRate = 9600) {
	EnhancedPort.Write(PingMessage, 0, 2);
	byte ReceivedID = Convert.ToByte(EnhancedPort.ReadByte());
	System.Threading.Thread.Sleep(200);
	if ((ReceivedID == DeviceID)) {
		byte[] BaudCode = { BaudToCode(BaudRate) };
		EnhancedPort.Write(BaudCode, 0, 1);
		EnhancedPort.BaudRate = BaudRate;
		ConnectionStatus = true;
	}
}

private void EndSerial(ref System.IO.Ports.SerialPort EnhancedPort) {
	EnhancedPort.Close();
}