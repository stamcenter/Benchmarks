/*  Benchmark: Stack Buffer Write
 *  @author  : Secure, Trusted, and Assured Microelectronics (STAM) Center

 *  Copyright (c) 2024 Memory Safety Benchmarks (STAM/SCAI/ASU)
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.

 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 */

#include <stdio.h>

typedef struct {
    double array[2];
    int flag;
} DoubleData;


int main() {
    DoubleData myData;
    myData.flag = 0;

    double userInput[] = {3.14, 2.71, 1.41, 1.73};  // Overflowing input

    for (size_t i = 0; i < 4; i++) {
        myData.array[i] = userInput[i]; // Potential overflow
    }

    if (myData.flag !=0 ) {
        printf("Test Failed: Stack Buffer Overflow within elements of struct with different sizes\n");
    } else {
        printf("Flag is normal.\n");
    }

    return 0;
}
