/*  Benchmark: Stack Buffer Overflow
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

typedef struct {
    int id;
    char name[10];
} Employee;


int main() {
    Employee employees[2] = {{.id = 0}, {.id = 1}};

    for (size_t i = 0; i < 2; i++) {
        strcpy(employees[i].name,  "\x61\x78\x61\x78\x30\x78\x61\x66\x66\x64\x65\x66\x66"); // Potential overflow
    }

    // Check if ID of any employee is altered
    for (size_t i = 0; i < 2; i++) {
        if (employees[i].id != i) {
            printf("Test Failed: Employee %zu ID altered due to overflow!\n",(i+1));
        }
    }

    return 0;
}
