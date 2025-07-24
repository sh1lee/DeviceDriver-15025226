#include "device_driver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
   int ret = (int)(m_hardware->read(address));
  
   for (int i = 0; i < 4; i++) {
       int temp = (int)(m_hardware->read(address));
       if (ret != temp) throw ReadFailException();
   }
    return ret;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    int temp = (int)(m_hardware->read(address));
    if (temp != 0xFF) throw WriteFailException();

    m_hardware->write(address, (unsigned char)data);
}
