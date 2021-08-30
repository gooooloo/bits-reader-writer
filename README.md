# bits-reader-writer

A lightweight util to streaming read/write bits from given `char` array.

## usage
Include `bits_reader_writer.h` in your source code, then use like this:

## read
``` C++
    unsigned char v[4] = { 0b10101010, 0b10101010, 0b10101010, 0b10101010 };

    gooooloo::BitsReader br(v, v+4);
    gooooloo::BitsV bv(0, 0);

    bv = br.read_bits(1);
    printf("read %d bits, expected value = 0b1, actual = 0x%x\n", bv.nbits, bv.v); 

    bv = br.read_bits(2);
    printf("read %d bits, expected value = 0b01, actual = 0x%x\n", bv.nbits, bv.v); 
```

## write
``` C++
    unsigned char v[2] = { 0 };
    gooooloo::BitsWriter bw(v, v+2);

    int nbits_written = bw.write_bits(gooooloo::BitsV(0b1, 1));
    if (nbits_written != 1) do_your_error_handling();
    // now v[0] is expected to be 0b10000000

    nbits_written = bw.write_bits(gooooloo::BitsV(0b1, 2));
    if (nbits_written != 2) do_your_error_handling();
    // now v[0] is expected to be 0b10100000
```

## demo
Check `demo.cpp` for more details!
``` bash
g++ demo.cpp && ./a.out
```