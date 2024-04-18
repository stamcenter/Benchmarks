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

/*  This vulnerability demonstrates an out of bounds write. It involves using a long
    instead of a char to write data from the last index of a string which causes an out
    of bounds write
    */

#include <stdio.h>
#include <stdlib.h>

void choice(int* d){
    
}

int main(){

    char str1[] = "PUBLIC";
    char str2[] = "VALUABLE DATA";

    char *a = &str1[0]; //Pointer to string 1
    char *b = &str2[0]; //Pointer to string 2

    printf("String 1: %s\n", a);
    printf("String 2: %s\n\n", b);


    unsigned int* d = (unsigned int *)(a+5); //a+5 is 'C' 

    printf("%x\n", *d); //Prints out 41560043; '41'='C' '00'=\0 56='V' 41='A'  

    if(*d == 0x41560043)
        printf("Test Failed: Pointer casting leads to Out of Bounds Read\n");


    return 0;
}

