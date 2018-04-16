# ******* Usage *******
#
# This script is the barebone for the serial communication
# The functions will not work if this script is imported in another script
#
# EnhancedPort is the serial port used in this example
#
# To connect call
# # \xOD represents the value 13 in HEX which is the default DeviceID
# # \x00\xFF represents the byte array { 0, 255 } in HEX which is the ping message used in the examples and can be changed from the Arduino code calling SetPingMessage
# # 115200 is the required baud rate. Change it to any baud rate supported
# ConnectSerial("\x0D", "\x00\xFF", 115200)
#
# In order to auto connect instead of calling ConnectSerial, call AutoConnect
# AutoConnect("\x0D", "\x00\xFF", 115200)
# Notice that AutoConnect returns True if the connection is successfully established

import time
import serial, serial.tools.list_ports

EnhancedPort = serial.Serial()
 
def BaudToCode(Baud):
    return {1200: "\x00", 2400: "\x01", 4800: "\x02", 9600: "\x03", 14400: "\x04",
    19200: "\x05", 8800: "\x06", 38400: "\x07", 57600: "\x08", 76800: "\x09",
    115200: "\x0A", 230400: "\x0B", 250000: "\x0C", 500000: "\x0D"}.get(Baud, "\x03")
 
def InitSerial(COMPort):
    global EnhancedPort
    EnhancedPort = serial.Serial(port=COMPort, baudrate=9600, timeout=2)
    EnhancedPort.setDTR(True)
    time.sleep(0.5)
    while EnhancedPort.in_waiting > 0:
        EnhancedPort.read()
 
def AutoConnect(DeviceID, PingMessage, BaudRate = 9600):
    global EnhancedPort
    COMPorts = serial.tools.list_ports.comports()
    for Port in COMPorts:
        InitSerial(Port.device)
        time.sleep(1.5)
        if ConnectSerial(DeviceID, PingMessage, BaudRate):
            return True
    return False
 
def ConnectSerial(DeviceID, PingMessage, BaudRate = 9600):
    global EnhancedPort
    EnhancedPort.write(PingMessage)
    ReceivedID = -1
    try:
        ReceivedID = ord(EnhancedPort.read())
    except:
        return False
    if ReceivedID == ord(DeviceID):
        BaudCode = BaudToCode(BaudRate)
        EnhancedPort.write(BaudCode)
        EnhancedPort.baudrate = BaudRate
        EnhancedPort.timeout = 0.5
        return True
		
# This will print True in the terminal if connection is established
print(AutoConnect("\x0D", "\x00\xFF", 115200))