#pragma once

#include <string>
#include <serial/serial.h>

class SerialConnection {
public:
    SerialConnection();
    ~SerialConnection();
    
    uint32_t send(const std::string signal);
    std::string receive();
    void setPort(const std::string port);
private:
    serial::Serial connection;
};
