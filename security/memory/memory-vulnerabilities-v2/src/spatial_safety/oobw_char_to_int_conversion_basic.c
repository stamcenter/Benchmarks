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

/*  This vulnerability demonstrates an out of bounds write. It involves using the conversion
    from char to int to store bytes beyond the expected bounds from a string in memory. An int 
    has 4 bytes and a char has 1 byte, hence by converting from char to int, we can store in 4x
    the allowable bounds in memory. However, for the int, 4 passes have to be done in order to 
    get all bytes in between each new int pointer.
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

    // Use a loop end point of size-2 to prevent exploit from being detected as stack smashing
    for(int i=0; i<public_string_size-2; i++){
        *(char *)(z+i) = 'A';
    }

    printf("%s\n", public_string);
    printf("%s\n", secret);

    for(int i=0; i<28; i++)
        if(secret[i] == 'A') {
            printf("Test Failed: Out of Bounds Write to adjacent array using char to int pointer conversion - Basic\n");
            break;
        }
}