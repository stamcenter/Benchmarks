/*  Benchmark: Data Oriented Programming
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

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main() {
    int exploit_input[10] = {55, 23, 45, 31, 88, 14, 32, 45, 32, 10};

    int buffer[5];  // Small buffer
    int adminAccess = 0;  // Variable controlling access

    char* adminAccessPointer=(char*)&adminAccess;
    char* bufferAddress=(char*)buffer;
    int bufferAccessDifference=adminAccessPointer-bufferAddress;

    // Using memcpy with the specified input length to cause buffer overflow
    //memcpy(buffer, exploit_input,bufferAccessDifference);
    for(int i=0; i<sizeof(exploit_input); i++) 
        buffer[i + bufferAccessDifference] = exploit_input[i];

    if (adminAccess) {
        printf("Test Failed: Data Oriented Programming - Overflow into adjacent variable\n");
    } else {
        printf("Regular user access.\n");
    }

    return 0;
}

