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

class Application {
public:
    Application(DeviceDriver* dd) : dd{ dd } {}
    void readAndPrint(long startAddr, long endAddr) {
        for (long addr = startAddr; addr <= endAddr; addr++) {
            dd->read(addr);
        }
    }
    void writeAll(unsigned char value) {
        for (long addr = 0x00; addr <= 0x04; addr++) {
            dd->write(addr, value);
        }
    }

private:
    DeviceDriver* dd;
};
