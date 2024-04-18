/*  Benchmark: Out of Bounds Write
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

/*  This vulnerability demonstrates an out of bounds write. Here, the goal is to 
    modify the size of an adjacent chunk, so that when freed and reallocated, the 
    modified chunk would overlap with a 3rd chunk
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char* c = malloc(0x10);
    char* d = malloc(0x10);
    char* e = malloc(0x10);

    printf("c: %p\n", c);
    printf("d: %p\n\n", d);

    *(c+0x18) = 0x31; //Manually edit size of d to a larger size so that it overlaps with e
    
    free(d); //Free d for a reallocation

    char* g = malloc(0x20); //Allocate a new variable with the increased size
    char* h = malloc(0x10); 
    
    // If the exploit succeeded, then d and g will be the same, otherwise d and h will be the same
    
    printf("g: %p\n", g);
    printf("h: %p\n", h);

    if(g == d)
        printf("Test Failed: Out of Bounds write to heap metadata\n");
     
}