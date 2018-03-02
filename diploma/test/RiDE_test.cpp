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
#include <gtest/gtest.h>

void fill_buffer(char * buf, char type, uint64_t id, uint64_t offset, 
        uint64_t len, uint32_t address, uint16_t port, char * data)
{
    rep64 nr1;
    rep64 nr2;
    rep64 nr3;
    rep32 nr4;
    rep16 nr5;
    uint64_t full_offset;
    switch(type)
    {
        case 'a': 
        {
            buf[0] = type;
            nr1.num = htobe64(id);
            nr2.num = htobe64(len);
            for(int i = 0; i < 8; i++)
            {
                buf[i+1]  = nr1.representation[i];
                buf[i+9]  = nr2.representation[i];
            }
            break;
        }
        case 'p': 
        {
            buf[0] = type;
            nr1.num = htobe64(id);
            nr2.num = htobe64(offset);
            nr3.num = htobe64(len);
            for(int i = 0; i < 8; i++)
            {
                buf[i+1]  = nr1.representation[i];
                buf[i+9]  = nr2.representation[i];
                buf[i+17] = nr3.representation[i];
            }
            full_offset = sizeof(type) + sizeof(id) + sizeof(offset) + 
                            sizeof(len) + offset;
            strncpy(buf + full_offset, data, len);
            break;
        }
        case 't':
        {
            buf[0] = type;
            nr1.num = htobe64(id);
            nr2.num = htobe64(offset);
            nr3.num = htobe64(len);
            nr4.num = htobe32(address);
            nr5.num = htobe16(port);
            for(int i = 0; i < 4; i++)
                buf[i+1] = nr4.representation[i];
            buf[5] = nr5.representation[0];
            buf[6] = nr5.representation[1];
            for(int i = 0; i < 8; i++)
            {
                buf[i+7]  = nr1.representation[i];
                buf[i+15] = nr2.representation[i];
                buf[i+23] = nr3.representation[i];
            }
            break;
        }
        default : break;
    }
}

TEST(RiDE_test, RiDE_unknown_command)
{
    datas_configure();
    char str[80];
    fill_buffer(str, 'd', 0, 0, 100, 0, 0, NULL);
    EXPECT_EQ(ERROR::UNKNOWN_COMMAND, parse_buffer(str));
    datas_dealloc();
}
 
TEST(RiDE_test, RiDE_simple_alloc)
{
    datas_configure();
    char str[80];
    fill_buffer(str, 'a', 0, 0, 100, 0, 0, NULL);
    EXPECT_EQ(ERROR::ALL_CORRECT, parse_buffer(str));
    datas_dealloc();
}

TEST(RiDE_test, RiDE_resize_alloc)
{
    datas_configure();
    char str1[80];
    char str2[80];
    char str3[80];
    fill_buffer(str1, 'a', 0, 0, 100, 0, 0, NULL);
    fill_buffer(str2, 'a', 1, 0, 100, 0, 0, NULL);
    fill_buffer(str3, 'a', 2, 0, 100, 0, 0, NULL);
    EXPECT_EQ(ERROR::ALL_CORRECT, parse_buffer(str1));
    EXPECT_EQ(ERROR::ALL_CORRECT, parse_buffer(str2));
    EXPECT_EQ(ERROR::ALL_CORRECT, parse_buffer(str3));
    datas_dealloc();
}

TEST(RiDE_test, RiDE_repeated_alloc)
{
    datas_configure();
    char str1[80];
    char str2[80];
    fill_buffer(str1, 'a', 0, 0, 100, 0, 0, NULL);
    fill_buffer(str2, 'a', 0, 0, 100, 0, 0, NULL);
    EXPECT_EQ(ERROR::ALL_CORRECT, parse_buffer(str1));
    EXPECT_EQ(ERROR::ALREADY_ALLOCATED, parse_buffer(str2));
    datas_dealloc();
}

TEST(RiDE_test, RiDE_too_big_block_alloc)
{
    datas_configure();
    char str1[80];
    fill_buffer(str1, 'a', 0, 0, uint64_t(-1) - 100000, 0, 0, NULL);
    EXPECT_EQ(ERROR::OUT_OF_MEMORY, parse_buffer(str1));
    datas_dealloc();
}

TEST(RiDE_test, RiDE_correct_placing)
{
    datas_configure();
    char str1[80];
    char str2[80];
    fill_buffer(str1, 'a', 0, 0, 100, 0, 0, NULL);
    fill_buffer(str2, 'p', 0, 0,   7, 0, 0, (char *)"Hello, ");
    EXPECT_EQ(ERROR::ALL_CORRECT, parse_buffer(str1));
    EXPECT_EQ(ERROR::ALL_CORRECT, parse_buffer(str2));
    datas_dealloc();
}

TEST(RiDE_test, RiDE_placing_on_wrong_id)
{
    datas_configure();
    char str1[80];
    fill_buffer(str1, 'p', 0, 0, 7, 0, 0, (char *)"Hello, ");
    EXPECT_EQ(ERROR::INCORRECT_ID, parse_buffer(str1));
    datas_dealloc();
}

TEST(RiDE_test, RiDE_placing_out_of_range)
{
    datas_configure();
    char str1[300];
    char str2[300];
    fill_buffer(str1, 'a', 0, 100, 0, 0, 0, NULL);
    fill_buffer(str2, 'p', 0, 100, 99, 8, 0, (char *)"Hello, ");
    EXPECT_EQ(ERROR::ALL_CORRECT, parse_buffer(str1));
    EXPECT_EQ(ERROR::OUT_OF_RANGE, parse_buffer(str2));
    datas_dealloc();
}

TEST(RiDE_test, RiDE_placing_with_resize)
{
    datas_configure();
    char str1[80];
    char str2[80];
    fill_buffer(str1, 'a', 0, 0, 100, 0, 0, NULL);
    fill_buffer(str2, 'a', 1, 0, 100, 0, 0, NULL);
    EXPECT_EQ(ERROR::ALL_CORRECT, parse_buffer(str1));
    EXPECT_EQ(ERROR::ALL_CORRECT, parse_buffer(str2));
    fill_buffer(str1, 'p', 0, 0, 7, 0, 0, (char *)"Hello, ");
    fill_buffer(str2, 'p', 1, 0, 7, 0, 0, (char *)"World! ");
    EXPECT_EQ(ERROR::ALL_CORRECT, parse_buffer(str1));
    EXPECT_EQ(ERROR::ALL_CORRECT, parse_buffer(str2));
    fill_buffer(str1, 'a', 2, 0, 100, 0, 0, NULL);
    EXPECT_EQ(ERROR::ALL_CORRECT, parse_buffer(str1));
    datas_dealloc();
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
