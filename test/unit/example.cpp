#include "gtest/gtest.h"
#include "gmock/gmock.h"
 
TEST(SampleTest, AssertionTrue) {
    ASSERT_EQ(1, 1);
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
