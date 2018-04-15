' ******* Usage *******
' 
' When main form loads
'
' ' SerialPort1 is the serial port component used in the program
' ' COM7 is the port the Arduino is connected to
' InitSerial(SerialPort1, "COM7")
'
' On connect button click
'
' ' 13 is the device ID used in the sample sketch and can be changed from the Arduino code
' ' {255, 255} is the default ping message used and can be changed from the Arduino code calling SetPingMessage
' ' 115200 is the required baud rate. Change it to any baud rate supported
' ConnectSerial(SerialPort1, 13, {255, 255}, 115200)
'
' In order to auto connect instead of calling ConnectSerial, call AutoConnect
' AutoConnect(SerialPort1, 13, {255, 255}, 115200)

Private Function BaudToCode(ByVal Baud As Integer) As Byte
	Select Case Baud
		Case 1200
			Return 0
		Case 2400
			Return 1
		Case 4800
			Return 2
		Case 9600
			Return 3
		Case 14400
			Return 4
		Case 19200
			Return 5
		Case 28800
			Return 6
		Case 38400
			Return 7
		Case 57600
			Return 8
		Case 76800
			Return 9
		Case 115200
			Return 10
		Case 230400
			Return 11
		Case 250000
			Return 12
		Case 500000
			Return 13
	End Select
	Return 3
End Function

Dim ConnectionStatus As Boolean = False

Private Sub InitSerial(ByRef EnhancedPort As IO.Ports.SerialPort, ByVal COMPort As String)
	ConnectionStatus = False
	If EnhancedPort.IsOpen() Then
		EndSerial(EnhancedPort)
	End If
	EnhancedPort.DtrEnable = True
	EnhancedPort.ReadTimeout = 2000
	EnhancedPort.BaudRate = 9600
	EnhancedPort.PortName = COMPort	
	EnhancedPort.Open()
	While EnhancedPort.BytesToRead > 0
		EnhancedPort.ReadByte()
	End While
End Sub

Private Function AutoConnect(ByRef EnhancedPort As IO.Ports.SerialPort, ByVal DeviceID As Byte, ByVal PingMessage As Byte(), ByVal Optional BaudRate As Integer = 9600) As Boolean
	For Each Port As String In IO.Ports.SerialPort.GetPortNames()
		Try
			InitSerial(EnhancedPort, Port)
			Threading.Thread.Sleep(2000)
			ConnectSerial(EnhancedPort, DeviceID, PingMessage, BaudRate)
			If ConnectionStatus Then
				Return True
			End If
		Catch Exception As Exception
		End Try
	Next
	Return False
End Function

Private Sub ConnectSerial(ByRef EnhancedPort As IO.Ports.SerialPort, ByVal DeviceID As Byte, ByVal PingMessage As Byte(), ByVal Optional BaudRate As Integer = 9600)
	EnhancedPort.Write(PingMessage, 0, 2)
	Dim ReceivedID As Byte = EnhancedPort.ReadByte()
	If ReceivedID = DeviceID Then
		Threading.Thread.Sleep(500)
		EnhancedPort.Write({BaudToCode(BaudRate)}, 0, 1)
		EnhancedPort.BaudRate = BaudRate
		EnhancedPort.ReadTimeout = 500
		ConnectionStatus = True
	End If
End Sub

Private Sub EndSerial(ByRef EnhancedPort As IO.Ports.SerialPort)
	EnhancedPort.Close()
	ConnectionStatus = False
End Sub