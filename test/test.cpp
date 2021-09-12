/*
* MIT License
* 
* Copyright (c) 2021 gooooloo
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include "../bits_reader_writer.h"
#include "gooooloo_test.h"

#define GOOOOLOO_ASSERT_READ_RESULT(x, y, z)  \
{                                             \
    gooooloo::BitsV _bv = (x);                \
    int _nbits = (y);                         \
    int _v = (z);                             \
    GOOOOLOO_ASSERT_EQUAL_INT(_nbits, _bv.nbits);      \
    GOOOOLOO_ASSERT_EQUAL_INT(_v, _bv.v);              \
}

GOOOOLOO_TEST(read_8bits_1by1)
{
    unsigned char v = 0b10101010;

    gooooloo::BitsReader reader(&v, &v+1);

    GOOOOLOO_ASSERT_READ_RESULT(reader.read_bits(1), 1, 0b1);
    GOOOOLOO_ASSERT_READ_RESULT(reader.read_bits(1), 1, 0b0);
    GOOOOLOO_ASSERT_READ_RESULT(reader.read_bits(1), 1, 0b1);
    GOOOOLOO_ASSERT_READ_RESULT(reader.read_bits(1), 1, 0b0);
    GOOOOLOO_ASSERT_READ_RESULT(reader.read_bits(1), 1, 0b1);
    GOOOOLOO_ASSERT_READ_RESULT(reader.read_bits(1), 1, 0b0);
    GOOOOLOO_ASSERT_READ_RESULT(reader.read_bits(1), 1, 0b1);
    GOOOOLOO_ASSERT_READ_RESULT(reader.read_bits(1), 1, 0b0);

    return 0;
}

GOOOOLOO_TEST(read_8bits_2by2)
{
    unsigned char v = 0b10100101;
    gooooloo::BitsReader reader(&v, &v+1);

    GOOOOLOO_ASSERT_READ_RESULT(reader.read_bits(2), 2, 0b10);
    GOOOOLOO_ASSERT_READ_RESULT(reader.read_bits(2), 2, 0b10);
    GOOOOLOO_ASSERT_READ_RESULT(reader.read_bits(2), 2, 0b01);
    GOOOOLOO_ASSERT_READ_RESULT(reader.read_bits(2), 2, 0b01);

    return 0;
}

GOOOOLOO_TEST(read_8bits_outofrange_from_beginning)
{
    unsigned char v = 0b10101011;
    gooooloo::BitsReader reader(&v, &v+1);

    GOOOOLOO_ASSERT_READ_RESULT(reader.read_bits(9), 8, 0b10101011);

    return 0;
}

GOOOOLOO_TEST(read_8bits_outofrange_from_middle)
{
    unsigned char v = 0b10101011;
    gooooloo::BitsReader reader(&v, &v+1);

    GOOOOLOO_ASSERT_READ_RESULT(reader.read_bits(7), 7, 0b1010101);
    GOOOOLOO_ASSERT_READ_RESULT(reader.read_bits(2), 1, 0b1);

    return 0;
}

GOOOOLOO_TEST(read_16bits_across_chars)
{
    unsigned char v[2] = { 0b10101010, 0b10101010 };
    gooooloo::BitsReader reader(v, v+2);

    GOOOOLOO_ASSERT_READ_RESULT(reader.read_bits(7), 7, 0b1010101);
    GOOOOLOO_ASSERT_READ_RESULT(reader.read_bits(3), 3, 0b010);
    GOOOOLOO_ASSERT_READ_RESULT(reader.read_bits(6), 6, 0b101010);

    return 0;
}

GOOOOLOO_TEST(read_whole)
{
    unsigned char v[2] = { 0b10101010, 0b10101010 };
    gooooloo::BitsReader reader(v, v+2);

    GOOOOLOO_ASSERT_READ_RESULT(reader.read_bits(16), 16, 0b1010101010101010);

    return 0;
}

GOOOOLOO_TEST(write_8_bits_1by1)
{
    unsigned char v =  0;
    gooooloo::BitsWriter writer(&v, &v+1);

    GOOOOLOO_ASSERT_EQUAL_INT(1, writer.write_bits(gooooloo::BitsV(0b1, 1)));
    GOOOOLOO_ASSERT_EQUAL_UCHAR(0b10000000, v);

    GOOOOLOO_ASSERT_EQUAL_INT(1, writer.write_bits(gooooloo::BitsV(0b1, 1)));
    GOOOOLOO_ASSERT_EQUAL_UCHAR(0b11000000, v);

    GOOOOLOO_ASSERT_EQUAL_INT(1, writer.write_bits(gooooloo::BitsV(0b1, 1)));
    GOOOOLOO_ASSERT_EQUAL_UCHAR(0b11100000, v);

    GOOOOLOO_ASSERT_EQUAL_INT(1, writer.write_bits(gooooloo::BitsV(0b1, 1)));
    GOOOOLOO_ASSERT_EQUAL_UCHAR(0b11110000, v);

    GOOOOLOO_ASSERT_EQUAL_INT(1, writer.write_bits(gooooloo::BitsV(0b1, 1)));
    GOOOOLOO_ASSERT_EQUAL_UCHAR(0b11111000, v);

    GOOOOLOO_ASSERT_EQUAL_INT(1, writer.write_bits(gooooloo::BitsV(0b1, 1)));
    GOOOOLOO_ASSERT_EQUAL_UCHAR(0b11111100, v);

    GOOOOLOO_ASSERT_EQUAL_INT(1, writer.write_bits(gooooloo::BitsV(0b1, 1)));
    GOOOOLOO_ASSERT_EQUAL_UCHAR(0b11111110, v);

    GOOOOLOO_ASSERT_EQUAL_INT(1, writer.write_bits(gooooloo::BitsV(0b1, 1)));
    GOOOOLOO_ASSERT_EQUAL_UCHAR(0b11111111, v);

    return 0;
}

GOOOOLOO_TEST(write_8_bits_2by2)
{
    unsigned char v =  0;
    gooooloo::BitsWriter writer(&v, &v+1);

    GOOOOLOO_ASSERT_EQUAL_INT(2, writer.write_bits(gooooloo::BitsV(0b11, 2)));
    GOOOOLOO_ASSERT_EQUAL_UCHAR(0b11000000, v);

    GOOOOLOO_ASSERT_EQUAL_INT(2, writer.write_bits(gooooloo::BitsV(0b11, 2)));
    GOOOOLOO_ASSERT_EQUAL_UCHAR(0b11110000, v);

    GOOOOLOO_ASSERT_EQUAL_INT(2, writer.write_bits(gooooloo::BitsV(0b11, 2)));
    GOOOOLOO_ASSERT_EQUAL_UCHAR(0b11111100, v);

    GOOOOLOO_ASSERT_EQUAL_INT(2, writer.write_bits(gooooloo::BitsV(0b11, 2)));
    GOOOOLOO_ASSERT_EQUAL_UCHAR(0b11111111, v);

    return 0;
}

GOOOOLOO_TEST(write_8_bits_outofrange_from_beginning)
{
    unsigned char v =  0;
    gooooloo::BitsWriter writer(&v, &v+1);

    GOOOOLOO_ASSERT_EQUAL_INT(8, writer.write_bits(gooooloo::BitsV(0b111111111, 9)));
    GOOOOLOO_ASSERT_EQUAL_UCHAR(0b11111111, v);

    return 0;
}

GOOOOLOO_TEST(write_8_bits_outofrange_from_middle)
{
    unsigned char v =  0;
    gooooloo::BitsWriter writer(&v, &v+1);

    GOOOOLOO_ASSERT_EQUAL_INT(2, writer.write_bits(gooooloo::BitsV(0b11, 2)));
    GOOOOLOO_ASSERT_EQUAL_UCHAR(0b11000000, v);

    GOOOOLOO_ASSERT_EQUAL_INT(6, writer.write_bits(gooooloo::BitsV(0b111111111, 9)));
    GOOOOLOO_ASSERT_EQUAL_UCHAR(0b11111111, v);

    return 0;
}

GOOOOLOO_TEST(write_16bits_across_chars)
{
    unsigned char v[2] = { 0, 0};
    gooooloo::BitsWriter writer(v, v+2);

    GOOOOLOO_ASSERT_EQUAL_INT(7, writer.write_bits(gooooloo::BitsV(0b1111111, 7)));
    GOOOOLOO_ASSERT_EQUAL_UCHAR(0b11111110, v[0]);
    GOOOOLOO_ASSERT_EQUAL_UCHAR(0b0, v[1]);

    GOOOOLOO_ASSERT_EQUAL_INT(2, writer.write_bits(gooooloo::BitsV(0b11, 2)));
    GOOOOLOO_ASSERT_EQUAL_UCHAR(0b11111111, v[0]);
    GOOOOLOO_ASSERT_EQUAL_UCHAR(0b10000000, v[1]);

    GOOOOLOO_ASSERT_EQUAL_INT(7, writer.write_bits(gooooloo::BitsV(0b1111111, 7)));
    GOOOOLOO_ASSERT_EQUAL_UCHAR(0b11111111, v[0]);
    GOOOOLOO_ASSERT_EQUAL_UCHAR(0b11111111, v[1]);

    return 0;
}

GOOOOLOO_TEST(write_whole)
{
    unsigned char v[2] = { 0, 0};
    gooooloo::BitsWriter writer(v, v+2);

    GOOOOLOO_ASSERT_EQUAL_INT(16, writer.write_bits(gooooloo::BitsV(0b1111111111111111, 16)));
    GOOOOLOO_ASSERT_EQUAL_UCHAR(0b11111111, v[0]);
    GOOOOLOO_ASSERT_EQUAL_UCHAR(0b11111111, v[1]);

    return 0;
}

int main() {
    return 0;
}