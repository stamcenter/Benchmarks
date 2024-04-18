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

/*  This vulnerability demonstrates a heap allocation exploit. It involves freeing
    chunks onto the tcache and then performing a use-after-free to modify chunk address.
    Thus, a chunk is artificially added to the tcache and can be allocated during a malloc
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    unsigned long int *ptr0, *ptr1, *target;

    ptr0 = malloc(0x10);
    ptr1 = malloc(0x10);
    target = malloc(0x10);

    printf("ptr0: %p\n", ptr0);
    printf("ptr1: %p\n", ptr1);
    printf("Target: %p\n\n", target);

    free(ptr0);
    free(ptr1);

    // Address of previous chunk is stored in ptr1. Increment by 64 to change this value to 
    // the address of the target
    *ptr1 = *ptr1+64; 
    // *ptr1 = *ptr1-64; //Use this line if previous line returns an address different from target 

    unsigned long int *ptr_x, *ptr_y, *ptr_z;

    ptr_x = malloc(0x10);
    ptr_y = malloc(0x10);

    printf("ptr_x: %p\n", ptr_x);
    printf("ptr_y: %p\n", ptr_y); //Value would be same as target

    if(ptr_y == target)
        printf("Test Failed: Heap manipulation leading to allocation on specific address\n");

    return 0;
}