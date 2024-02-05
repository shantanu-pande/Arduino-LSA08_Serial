#ifndef LSA08_h
    #define LSA08_h
    #include "Arduino.h"

class LSA08_Serial
{
private:
    char _UART_ADDR;
    uint8_t _SER_EN;
    HardwareSerial *LSA_SERIAL;

public:
    LSA08_Serial(HardwareSerial &SER, char UART_ADDR, uint8_t SER_EN);
    ~LSA08_Serial();
    int readInt();
    byte readByte();
    byte readRaw();
    void begin(int buadrate);
    void calibrate();
    void sendCommand(char command, char data);
    void setLineThresh(char data);
    void setJWidth(char data);
    void setUARTaddr(char data);
    void setLCDbacklit(char data);
    void setLCDcontrast(char data);
    void setUARTbuadrate(char data);
    void setUARTmode(char data);
    void clearJunction();
    unsigned int getJunctionCount();
    void positionIntegerOutput();
    void positionRawOutput();
    void positionByteOutput();
    void lineMode(char data);
};

#endif