const SerialPort = require('serialport');

module.exports = class EnchancedSerial {

  port;
  connection;

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
        this.port.on('readable', function () {
          this.dataReceived(port.read());
        })
        return;
      });
    } catch (error) {
      throw new Error();
    }
  }

  dataReceived(data) {
    this.connection = true;
  }

  autoConnect(deviceID, pingMessage, baudRate = 9600) {
    this.port.write(pingMessage);
    setTimeout(() => {
      return this.connection;
    }, 5000);
  }

};


let x = new EnchancedSerial();
x.autoConnect("\x0D", "\x00\xFF", 115200);