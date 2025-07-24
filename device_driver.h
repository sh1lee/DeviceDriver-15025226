#pragma once
#include <stdexcept>
#include "flash_memory_device.h"

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);


protected:
    FlashMemoryDevice* m_hardware;
};

class ReadFailException : public std::exception {
public:
    char const* what() const override {
        return "ReadFailException";
    }
};
class WriteFailException : public std::exception {
public:
    char const* what() const override {
        return "WriteFailException";
    }
};
