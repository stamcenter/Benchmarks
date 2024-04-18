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

/*  This vulnerability demonstrates an out of bound read. It involves directly
    indexing an integer array with a value greater than it's size. 
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    int arr1[] = {2,4,6,8,10}; // Array with 5 elements; Last element is indexed by arr1[4]
    int arr2[] = {1,3,5,7,9};

    printf("%p\n", &arr1[0]);
    printf("%p\n\n", &arr2[0]);
    long *target = (long *)(&arr1[8]);
    *target = 0x44454B4341482121;

    for(int i=0;i<5;i++){
        printf("%d ", arr2[i]);
    }
    printf("\n");


    for(int i=0;i<5;i++)
        if( arr2[i] > 9) {
            printf("Test Failed: Int array on heap using long pointer Out of Bounds Write\n");
            break;
        }

    return 0;
}