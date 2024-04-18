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

/*  This vulnerability demonstrates an out of bound read. It involves directly
    indexing an element of a string with an index greater than the string's length. 
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    char str1[] = "abcde";
    char str2[] = "fghij";

    // The string ends with a null terminator so an out of bounds write would 
    // involve adding incrementing by 2 or more indexes from the last element 
    // in the string
    
    printf("Last element of string 1 is: %c\n", str1[4]);
    printf("Null terminator for string 1: %d\n", str1[5]);
    printf("Out of bounds read: %c\n", str1[6]);

    if(str1[6]!= 0)
        printf("Test Failed: Simple String Out of Bounds Read\n");

    return 0;
}