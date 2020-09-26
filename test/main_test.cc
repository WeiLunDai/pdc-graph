
#include <gtest/gtest.h>
#include "graph_test_suite.h"
// add new test suite on the above
// this is entry point for test

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
