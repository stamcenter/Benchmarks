/*  Benchmark: Stack Buffer Overflow
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
    int hiddenValues[3];
    int triggerCheck;
} IntData;

int main() {
    IntData vaultData;
    vaultData.triggerCheck = 0x0; // Initialized to 0 in hexadecimal

    int attackSequence[] = {0x1, 0x2, 0x3, 0x4, 0x3039}; // Malicious input with hex values

    for (size_t idx = 0; idx < 5; idx++) {
        vaultData.hiddenValues[idx] = attackSequence[idx]; // No boundary check
    }

    if (vaultData.triggerCheck != 0x0) {
        printf("Test Failed: Stack Buffer Overflow within struct elements of int datatype\n");
    } else {
        printf("Trigger Check intact.\n");
    }

    return 0;
}
