/*  Benchmark: Use After Free
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

/*  This vulnerability demonstrates a double free. It involves an error where a second
    if block is used instead of an else if, leading to a free being executed twice
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *ptr = malloc(0x10);
    
    memcpy(ptr, "VALUABLE VALUE", 0x10);

    int trig_count = 0;

    if (ptr != "HELLO") {
        memcpy(ptr, "NOT HELLO", 0x10);
        printf("pointer changed to %s\n", ptr);
        free(ptr);
        trig_count++;
    }if (ptr != "WORLD") {
        memcpy(ptr, "NOT WORLD", 0x10);
        printf("pointer changed to %s\n", ptr);
        free(ptr);
        trig_count++;

    }if (ptr != "") {
        memcpy(ptr, "NOT EMPTY", 0x10);
        printf("pointer changed to %s\n", ptr);
        free(ptr);
        trig_count++;
    }

    if(trig_count>1)
        printf("Test Failed: Repeated free operations caused by incorrect branching\n");

    return 0;
}