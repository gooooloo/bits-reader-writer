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

#include <stdio.h>
#include "bits_reader_writer.h"

void demo_read() {
    unsigned char v[4] = { 0b10101010, 0b10101010, 0b10101010, 0b10101010 };

    gooooloo::BitsReader br(v, v+4);
    gooooloo::BitsV bv(0, 0);

    bv = br.read_bits(1);
    printf("read %d bits, expected value = 0b1, actual = 0x%x\n", bv.nbits, bv.v); 

    bv = br.read_bits(2);
    printf("read %d bits, expected value = 0b01, actual = 0x%x\n", bv.nbits, bv.v); 

    bv = br.read_bits(4);
    printf("read %d bits, expected value = 0b0101, actual = 0x%x\n", bv.nbits, bv.v); 

    bv = br.read_bits(3);
    printf("read %d bits, expected value = 0b010, actual = 0x%x\n", bv.nbits, bv.v); 

    bv = br.read_bits(5);
    printf("read %d bits, expected value = 0b10101, actual = 0x%x\n", bv.nbits, bv.v); 

    bv = br.read_bits(12);
    printf("read %d bits, expected value = 0b010101010101, actual = 0x%x\n", bv.nbits, bv.v); 

    bv = br.read_bits(6); // Note this hits an out-of-range case. Check the result.
    printf("read %d bits, expected value = 0b01010, actual = 0x%x\n", bv.nbits, bv.v); 
}

void demo_write() {
    unsigned char v[4] = { 0 };

    gooooloo::BitsWriter bw(v, v+4);
    int nbits_written = 0;

    nbits_written = bw.write_bits(gooooloo::BitsV(0b1, 1));
    printf("write %d bits\n", nbits_written);

    nbits_written = bw.write_bits(gooooloo::BitsV(0b01, 2));
    printf("write %d bits\n", nbits_written);

    nbits_written = bw.write_bits(gooooloo::BitsV(0b0101, 4));
    printf("write %d bits\n", nbits_written);

    nbits_written = bw.write_bits(gooooloo::BitsV(0b010, 3));
    printf("write %d bits\n", nbits_written);

    nbits_written = bw.write_bits(gooooloo::BitsV(0b10101, 5));
    printf("write %d bits\n", nbits_written);

    nbits_written = bw.write_bits(gooooloo::BitsV(0b010101010101, 12));
    printf("write %d bits\n", nbits_written);

    // Note this hits an out-of-range case. Check the result.
    nbits_written = bw.write_bits(gooooloo::BitsV(0b010101, 6));
    printf("write %d bits\n", nbits_written);

    printf("v[0] expected = 0b10101010, actual = 0x%x\n", v[0]);
    printf("v[1] expected = 0b10101010, actual = 0x%x\n", v[1]);
    printf("v[2] expected = 0b10101010, actual = 0x%x\n", v[2]);
    printf("v[3] expected = 0b10101010, actual = 0x%x\n", v[3]);
}

int main() {
    demo_read();
    demo_write();

    return 1;
}