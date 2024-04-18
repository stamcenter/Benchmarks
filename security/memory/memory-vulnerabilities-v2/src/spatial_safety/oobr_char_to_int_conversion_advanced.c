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

/*  This vulnerability demonstrates an out of bounds read. It involves using the conversion
    from char to int to print extra bytes than expected from a string in memory. An int has
    4 bytes and a char has 1 byte, hence by converting from char to int, we can print out 4x
    the amout of memory. However, for the int, 4 passes have to be done in order to get all 
    bytes in between each new int pointer.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char public_string[] = "public string\0";
    char secret[] = "This is the secret in memory\0";

    int public_string_size = sizeof(public_string)/sizeof(public_string[0]);

    char *y = &public_string[0];
    int *z = (int*)y;

    int test_status = 1;

    // printing using char pointer
    for(int i=0; i<public_string_size; i++){
        printf("%p ", (y+i)); //y+i increments y by one byte
        printf("%c \n", *(y+i));
    }
    printf("\n");

    for(int i=0; i<public_string_size; i++){
        /*
        Char pointer y is first converted to an int pointer and the array index i is used to 
        iterate through the string.
        However, conversion to int means that pointers are spaced out by 4 bytes, so a second loop
        is used to reference all bytes in-between
        */ 
        char *q = (char *)(((int*)y)+i);
        
        for(int j=0; j<4; j++){
            char* val = (char *)((int*)(q+j));
            printf("%p ", val);
            printf("%c\n", *val);
            if(val>(public_string+sizeof(public_string)) && *val!=0)
                test_status = 0;
        }
    }
    printf("\n");
    if(!test_status)
        printf("Test Failed: Out of Bounds Read by Char to Int Conversion Advanced\n");
}