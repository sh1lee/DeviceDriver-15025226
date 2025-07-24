#include "gmock/gmock.h"
#include "device_driver.h"
#include <string>
using namespace std;
using namespace testing;
class FlashMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
	
};

TEST(DeviceDriver, FiveRead) {
	FlashMock mock;
	EXPECT_CALL(mock, read((long)0xB))
		.Times(5);

	DeviceDriver driver{ &mock };
	int data = driver.read((long)0xB);

}
TEST(DeviceDriver, ReadFailExpcetion) {
	FlashMock mock;

	EXPECT_CALL(mock, read((long)0xB))
		.WillOnce(Return((unsigned char)0xA))
		.WillOnce(Return((unsigned char)0xA))
		.WillOnce(Return((unsigned char)0xA))
		.WillOnce(Return((unsigned char)0xA))
		.WillOnce(Return((unsigned char)0xB));

	DeviceDriver driver{ &mock };

	EXPECT_THROW(driver.read((long)0xB), ReadFailException);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}