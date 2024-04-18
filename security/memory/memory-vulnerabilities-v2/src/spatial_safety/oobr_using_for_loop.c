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

/*  This vulnerability demonstrates an out of bound write. It involves using a for
    loop to iterate over an array and set elements. However the maximum index of 
    the for loop is greater than the length of the array
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    char str1[] = "random";
    char str2[] = "This is the second string";

    int str1_len = sizeof(str1)/sizeof(str1[0]);
    int str2_len = sizeof(str2)/sizeof(str2[0]);

    printf("String 1 length is: %d\n", str1_len);
    printf("String 2 length is: %d\n", str2_len);

    int test_status = 0;

    // The length of string 2 was used to print out string 1
    for(int i=0; i<str2_len; i++){
        printf("%c", str1[i]);
        if(i>=str1_len && str1[i] != 0)
            test_status = 1;
    }
    printf("\n");

    if(test_status == 1)
        printf("Test Failed: Out of Bounds Read using simple for loop\n");

    return 0;
}