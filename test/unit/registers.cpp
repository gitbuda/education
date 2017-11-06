#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "registers/sequential.hpp"
#include "registers/safe_bool_mrsw.hpp"
#include "registers/regular_bool_mrsw.hpp"

TEST(SequentialRegister, Registers) {
    registers::Sequential<int> reg;
    reg.Write(1);
    ASSERT_EQ(reg.Read(), 1);
}

TEST(SafeBoolMRSW, Registers) {
    registers::SafeBoolMRSW reg(1);
    reg.Write(1);
    ASSERT_EQ(reg.Read(), 1);
}

TEST(RegularBoolMRSW, Registers) {
    registers::RegularBoolMRSW reg;
    reg.Write(true);
    ASSERT_EQ(reg.Read(), true);
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
