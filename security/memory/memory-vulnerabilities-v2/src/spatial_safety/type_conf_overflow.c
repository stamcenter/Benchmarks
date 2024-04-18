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
 */
#include <stdio.h>
#include <stdlib.h>

char* get_buf(short size) {
    printf("Allocating buffer of size %d\n", size);

    void *ptr = malloc(size);

    printf("Bounds of allocated buffer: %p - %p\n", ptr, ptr+size);

    return ptr; 
}

int main(void) {

    int test_status = 1;

    int user_input = (1<<16) | 16;
    printf("Requesting buffer of size %d\n", user_input);

    char *buf = (char *)get_buf(user_input);  // Smaller buffer is allocated because of overflow from int to short

    int index = 100;                  // Access item withing original buffer range but not part of allocated buffer
    if(index < user_input) {
        buf[index] = 0x41;
        printf("Retrieved value at address %p: 0x%x\n", &buf[index], buf[index]);    

        if(buf[index] == 0x41)        // Check if write/read is permitted and not just ignored
            test_status = 0;
    }

    if(test_status == 0)
        printf("Test Failed: OOB access caused by int->short overflow\n");
}
