#include <LSA08_Serial.h>


LSA08_Serial::LSA08_Serial(HardwareSerial &SER, char UART_ADDR, uint8_t SER_EN)
{
    LSA_SERIAL = &SER;
    _SER_EN = SER_EN;
    _UART_ADDR = UART_ADDR;
}
LSA08_Serial::~LSA08_Serial(){}


void LSA08_Serial::begin(int buadrate)
{
    LSA_SERIAL->begin(buadrate);
    LSA_SERIAL->flush();
    LSA_SERIAL->setTimeout(100);
    pinMode(_SER_EN, OUTPUT);
    digitalWrite(_SER_EN, HIGH);
}

void LSA08_Serial::sendCommand(char command, char data)
{
    char checksum = _UART_ADDR + command + data;
    LSA_SERIAL->write(_UART_ADDR);
    LSA_SERIAL->write(command);
    LSA_SERIAL->write(data);
    LSA_SERIAL->write(checksum);
}

void LSA08_Serial::calibrate()
{
    sendCommand('C', 0x00);
}

void LSA08_Serial::setLineThresh(char data)
{
    sendCommand('T', data);
}

void LSA08_Serial::setJWidth(char data)
{
    sendCommand('J', data);
}

void LSA08_Serial::setUARTaddr(char data)
{
    sendCommand('A', data);
}

void LSA08_Serial::setLCDbacklit(char data)
{
    sendCommand('B', data);
}

void LSA08_Serial::setLCDcontrast(char data)
{
    sendCommand('S', data);
}

void LSA08_Serial::setUARTbuadrate(char data)
{
    sendCommand('R', data);
}

void LSA08_Serial::setUARTmode(char data)
{
    sendCommand('D', data);
}

void LSA08_Serial::clearJunction()
{
    sendCommand('X', 0x00);
}

unsigned int LSA08_Serial::getJunctionCount()
{
    sendCommand('X', 0x01);

    unsigned int dummy = 0;
	digitalWrite(_SER_EN,LOW); 
	while(LSA_SERIAL->available() <= 0);
	dummy = LSA_SERIAL->read();
	digitalWrite(_SER_EN,HIGH);

    return dummy;
}

void LSA08_Serial::positionByteOutput()
{
    sendCommand('P', 0x01);
}

void LSA08_Serial::positionIntegerOutput()
{
    sendCommand('P', 0x02);
}

void LSA08_Serial::positionRawOutput()
{
    sendCommand('P', 0x03);
}

int LSA08_Serial::readInt()
{
    positionIntegerOutput();
    int dummy;

    digitalWrite(_SER_EN,LOW); 
	while(LSA_SERIAL->available() <= 0);
	dummy = LSA_SERIAL->read();
	digitalWrite(_SER_EN,HIGH);

    return dummy;
}

byte LSA08_Serial::readByte()
{
    positionByteOutput();
    byte dummy;

    digitalWrite(_SER_EN,LOW); 
	while(LSA_SERIAL->available() <= 0);
	dummy = LSA_SERIAL->read();
	digitalWrite(_SER_EN,HIGH);

    return dummy;
}

byte LSA08_Serial::readRaw()
{
    positionRawOutput();
    int dummy;

    digitalWrite(_SER_EN,LOW); 
	while(LSA_SERIAL->available() <= 0);
	dummy = LSA_SERIAL->read();
	digitalWrite(_SER_EN,HIGH);

    return dummy;
}

void LSA08_Serial::lineMode(char data)
{
    sendCommand('L', data);
}