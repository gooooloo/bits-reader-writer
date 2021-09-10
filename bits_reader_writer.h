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

#ifndef BITS_READER_WRITER_H
#define BITS_READER_WRITER_H

namespace gooooloo {

struct BitsV {
    int v;
    int nbits;
    BitsV(int _v, int _nbits) : v(_v), nbits(_nbits) {}
};

class BitsReader {
    unsigned char *pnext;
    unsigned char *pend;
    unsigned char char_cur;
    unsigned char nbits_cur;

public:
    BitsReader(unsigned char *_pstart, unsigned char *_pend) {
        pnext = _pstart;
        pend = _pend;
        char_cur = 0;
        nbits_cur = 0;
    }

    BitsV read_bits(int nbits_to_read) {
        BitsV bv(0, 0);

        while (nbits_to_read > 0) {
            if (nbits_cur <= 0) {
                if (pnext >= pend) {
                    return bv;
                } else {
                    char_cur = *pnext++;
                    nbits_cur = 8;
                }
            }

            const int k = nbits_to_read > nbits_cur ? nbits_cur : nbits_to_read;

            const int nbits_cur_new = nbits_cur - k;
            const int nbits_to_read_new = nbits_to_read - k;

            const int mask = (1 << nbits_cur) - 1;
            bv.v = (bv.v << k) | ((char_cur & mask) >> nbits_cur_new);
            bv.nbits += k;

            nbits_cur = nbits_cur_new;
            nbits_to_read = nbits_to_read_new;
        }

        return bv;
    }
};

class BitsWriter {
    unsigned char *pnext;
    unsigned char *pend;
    unsigned char *pcur;
    unsigned char nbits_cur;

public:
    BitsWriter(unsigned char *_pstart, unsigned char *_pend) {
        pnext = _pstart;
        pend = _pend;
        pcur = 0;
        nbits_cur = 0;
    }

    int write_bits(BitsV bv) {
        int nbits_written = 0;

        while (bv.nbits > 0) {
            if (nbits_cur <= 0) {
                if (pnext >= pend) {
                    return nbits_written;
                } else {
                    pcur = pnext++;
                    nbits_cur = 8;
                }
            }

            const int k = (nbits_cur > bv.nbits) ? bv.nbits : nbits_cur;

            const int nbits_bv_new = bv.nbits - k;
            const int nbits_cur_new = nbits_cur - k;

            const int mask = ((1 << bv.nbits) - 1);
            *pcur |= (bv.v & mask) >> nbits_bv_new << nbits_cur_new;
            nbits_written += k;

            bv.nbits = nbits_bv_new;
            nbits_cur = nbits_cur_new;
        }

        return nbits_written;
    }
};

} // namespace gooooloo

#endif // BITS_READER_WRITER_H