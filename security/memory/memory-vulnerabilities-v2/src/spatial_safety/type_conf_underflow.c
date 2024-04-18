/*  Benchmark: Type Confusion
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
 */#include <stdio.h>

// Vulnerable function which has the int->short casting issue
char get_char(short offset) {
   char *private = "AAAAAA";
   char *public = "Public";

   return public[offset];     // First 6 characters of the string should not be accessible
}

int main(void) {
    int num = (1<<16);
    int underflow_loc = 2;   // How many bytes away from start of buffer to read. 2 to include null character from previous string

    num -= underflow_loc;    // Int to short underflow causes this to be -(underflow_loc)

    int test_status = 1;

    printf("Fetching char at index %d\n", num);
    char c = get_char(num);
    printf("Fetched char: %c\n", c);

    if(c == 0x41)            // Check if access to private string was successful
        test_status = 0;

    if(test_status == 0)
        printf("Test Failed: OOB access caused by int->short overflow leading to array underread\n");
}
