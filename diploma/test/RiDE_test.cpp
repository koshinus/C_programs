/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ride_test.cpp
 * Author: vadim
 *
 * Created on 7 декабря 2017 г., 6:36
 */
#include "../src/RiDE_server.c"
#include "../src/test.c"
#include <gtest/gtest.h>

/*
 * 
#define ALL_CORRECT         0
#define UNKNOWN_COMMAND     1
#define INCORRECT_ID        2
#define ALREADY_ALLOCATED   3
#define OUT_OF_MEMORY       4
#define OUT_OF_RANGE        5
 */

TEST(RiDE_test, RiDE_unknown_command)
{ 
    EXPECT_EQ(UNKNOWN_COMMAND, unknown_command());
}
 
TEST(RiDE_test, RiDE_simple_alloc)
{ 
    EXPECT_EQ(ALL_CORRECT, simple_alloc());
}

TEST(RiDE_test, RiDE_resize_alloc)
{ 
    EXPECT_EQ(ALL_CORRECT, resize_alloc());
}

TEST(RiDE_test, RiDE_repeated_alloc)
{
    EXPECT_EQ(ALREADY_ALLOCATED, repeated_alloc());
}

/*
 * Bag: malloc(sizeof(char) * uint64_t(-1)) does not allocate memory
 * 
TEST(RiDE_test, RiDE_too_big_block_alloc)
{
    EXPECT_EQ(OUT_OF_MEMORY, too_big_block_alloc());
}
*/

TEST(RiDE_test, RiDE_correct_placing)
{
    EXPECT_EQ(ALL_CORRECT, correct_placing());
}

TEST(RiDE_test, RiDE_placing_on_wrong_id)
{
    EXPECT_EQ(INCORRECT_ID, placing_on_wrong_id());
}

TEST(RiDE_test, RiDE_placing_out_of_range)
{
    EXPECT_EQ(OUT_OF_RANGE, placing_out_of_range());
}

TEST(RiDE_test, RiDE_placing_with_resize)
{
    EXPECT_EQ(ALL_CORRECT, placing_with_resize());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}