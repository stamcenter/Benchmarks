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

/*  This vulnerability demonstrates an out of bounds write. It consists of an off-by-one
    error caused by incrementing an iterator at the wrong part of a do while loop.
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    int num_elems = 5;
    int nums[] = {0,0,0,0,0};
    
    // incorrectly using a do-while loop
    // placing 
    int i=0;
    do{
        i++;
        nums[i] = i*2;
    }while(i < num_elems);

    for(int i=0; i<=num_elems; i++){
        printf("i: %d \tval: %d\n", i, nums[i]);
    }

    if(nums[5] == 10)
    printf("Test Failed: Incorrect usage of do-while loop leading to Out of Bounds Write\n");
    
}