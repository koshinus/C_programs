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
 */
TEST(RiDE_test, RiDE_memory_managment)
{ 
    ASSERT_EQ(1, unknown_command());
    //ASSERT_EQ(18.0, squareRoot(324.0));
    //ASSERT_EQ(25.4, squareRoot(645.16));
    //ASSERT_EQ(0, squareRoot(0.0));
}
 
TEST(RiDE_test, RiDE_network_interaction)
{
    //ASSERT_EQ(-1.0, squareRoot(-15.0));
    //ASSERT_EQ(-1.0, squareRoot(-0.2));
}
 
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}