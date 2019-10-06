#include "serialConnection.hpp"

SerialConnection::SerialConnection()
{
    connection.setBaudrate(115200);
    serial::Timeout timeout = serial::Timeout::simpleTimeout(UINT32_MAX);
    connection.setTimeout(timeout);
}

SerialConnection::~SerialConnection()
{
    if (connection.isOpen())
        connection.flush();
    connection.close();
}

uint32_t SerialConnection::send(const std::string signal)
{
    uint32_t bytes = connection.write(signal);
    if (!bytes) {
        std::runtime_error("Failed to send signal!");
    }
    
    return bytes;
}

std::string SerialConnection::receive()
{
    return connection.readline();
}

void SerialConnection::setPort(const std::string port)
{
    if (connection.isOpen())
        connection.close();
        
    connection.setPort(port);
    connection.open();
}
