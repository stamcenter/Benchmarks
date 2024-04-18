/*  Benchmark: Out of Bounds Read
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

/*  This vulnerability demonstrates an out of bounds read. It involves first performing
    a buffer overflow to overwrite the string terminating bits between 2 adjacent chunks.
    Thus a call to printf would be able to print out the memory of both chunks 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char* c = malloc(0x10);
    char* d = malloc(0x20);
    char* e = malloc(0x10);

    printf("c: %p\n", c);
    printf("d: %p\n", d);
    printf("e: %p\n\n", e);

    memcpy(d, "This is a secret!!!", 0x20);
    // *(c+0x18) = 0x31; //Manually edit size of d to a larger size so that it overlaps with e
    memcpy(c, "11111111111111111111111111111111", 0x20); //Manually edit size of d to a larger size so that it overlaps with e

    printf("c: %s\n", c);
    int iter = 0;
    while(c[iter] != 0) {
        if(c[iter] != '1'){
            printf("Test Failed: Out of Bounds Read caused by string null terminator corruption\n");
            break;
        }
        iter++;
}
            

    free(c);
    
    // The overflow corrupted the metadata of d so we need to correct the metadata before freeing d
    // Otherwise a metadata corruption would be detected and the exploit would fail
    memcpy(c, "1111111111111111111111111\0\0\0\0\0\0\0A", 0x30); //Manually edit size of d to a larger size so that it overlaps with e
    free(d); //Free d for a reallocation
    
    // printf("h: %p\n", h);
     
}