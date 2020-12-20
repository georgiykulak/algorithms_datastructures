#ifndef __DATASTRUCTURES_COMMON_GTEST_HELPER__
#define __DATASTRUCTURES_COMMON_GTEST_HELPER__

#include "gtest/gtest.h"

#define TESTBENCH()                         \
    int main( int c, char** v )             \
    {                                       \
        ::testing::InitGoogleTest( &c, v ); \
        return RUN_ALL_TESTS();             \
    }

#endif /* __DATASTRUCTURES_COMMON_GTEST_HELPER__ */