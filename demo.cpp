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