#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "data_structure/queue/lock.hpp"
 
TEST(LockQueue, PushPop)
{
    data_structure::LockQueue<int> queue(1);
    queue.push(1);
    auto value = queue.pop();    
    EXPECT_EQ(value, 1);
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
