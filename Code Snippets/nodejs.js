const SerialPort = require('serialport');

module.exports = class EnchancedSerial {

  port;

  constructor() {
    this.port = undefined;
    this.findProperPort();
  }

  async findProperPort() {
    const ports = await SerialPort.list();
    try {
      ports.forEach(port => {
        this.port = new SerialPort(port, {
          baudRate: 57600
        })
        return;
      });
    } catch (error) {
      throw new Error();
    }
  }

  autoConnect(deviceID, pingMessage, baudRate = 9600) {
    this.port.write(pingMessage);
  }

};


let x = new EnchancedSerial();
x.autoConnect("\x0D", "\x00\xFF", 115200);