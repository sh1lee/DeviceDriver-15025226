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
TEST(DeviceDriver, ReadFailExceptionTC) {
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

TEST(DeviceDriver, ReadBeforeWrite) {
	FlashMock mock;

	EXPECT_CALL(mock, read((long)0xB))
		.Times(1)
		.WillRepeatedly(Return((unsigned char)0xFF));

	DeviceDriver driver{ &mock };

	driver.write((long)0xB,7);
}
TEST(DeviceDriver, WriteFailExceptionTC) {
	FlashMock mock;

	EXPECT_CALL(mock, read((long)0xB))
		.WillOnce(Return((unsigned char)0xA));

	DeviceDriver driver{ &mock };

	EXPECT_THROW(driver.write((long)0xB, 7), WriteFailException);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}