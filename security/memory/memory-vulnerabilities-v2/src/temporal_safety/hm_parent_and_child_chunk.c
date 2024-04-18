/*  Benchmark: Heap Manipulation
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

/*  This vulnerability demonstrates a heap manipulation exploit. It involves first
    using an out of bounds write to make the range of one chunk extend past the range 
    of a formally subsequent chunk. Thus the memory range of the second chunk would be 
    inside the range of the first. These chunks are then feed and reallocated. Thus
    any edit made on the larger chunk would be legal, regardless of whether the memory
    written to or read from was within the space of the smaller chunk.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char* c = malloc(0x10);
    char* d = malloc(0x10);
    char* e = malloc(0x10);


    *(c+0x18) = 0x61; //Manually edit size of d to a larger size so that it overlaps with e
    
    free(d); //Free d for a reallocation
    free(e); //Free e for a reallocation

    /* 
      If a malloc is done for h with the size of e and for g with the adjusted size of d, 
      and is successful, then the memory allocated to h would be a subset of the memory
      allocated to g. Thus g would be able to legally control the contents of the memory 
      allocated to h
    */
    
    char* g = malloc(0x50); //Allocate a new variable with the increased size
    char* h = malloc(0x10); 
    
    // If the exploit succeeded, then d and g will be the same, otherwise d and h will be the same
    
    memcpy(h, "victim's data", 0xe); //h copies in some data needed for program control
    
    memset(g+0x20, 0x41, 0xf); // This position is still within the legal memory range of g but the memory region overlaps with h


    printf("d: %p\n", d);
    printf("e: %p\n\n", e);

    printf("g: %p -> %p\n", g, (g+0x50));
    printf("h: %p\n", h);
    printf("h: %s\n", h);

    if(h[0] == 'A')
      printf("Test Failed: Heap manipulation leading to overlapping memory regions\n");
    

}