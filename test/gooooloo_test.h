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

#ifndef GOOOOLOO_TEST_H
#define GOOOOLOO_TEST_H

#include <stdio.h>

#define GOOOOLOO_ASSERT_EQUAL_INT( x, y )     \
{                                             \
  int _x = (x);                               \
  int _y = (y);                               \
  if( ( _x ) != ( _y ) )                      \
  {                                           \
    printf( "test error\n"                    \
            "file:%s\n"                       \
            "line:%d\n"                       \
            "exp:%d\n"                        \
            "act:%d\n",                       \
            __FILE__, __LINE__, (_x), (_y));  \
    return 1;                                 \
  }                                           \
}

#define GOOOOLOO_ASSERT_EQUAL_UCHAR( x, y )   \
{                                             \
  unsigned char _x = (x);                     \
  unsigned char _y = (y);                     \
  if( ( _x ) != ( _y ) )                      \
  {                                           \
    printf( "test error\n"                    \
            "file:%s\n"                       \
            "line:%d\n"                       \
            "exp:%d\n"                        \
            "act:%d\n",                       \
            __FILE__, __LINE__, (_x), (_y));  \
    return 1;                                 \
  }                                           \
}

#define GOOOOLOO_TEMP_VAR(x) x##__
#define GOOOOLOO_TEST(testname)               \
int testname();                               \
int GOOOOLOO_TEMP_VAR(testname) = testname(); \
int testname()

#endif // GOOOOLOO_TEST_H
