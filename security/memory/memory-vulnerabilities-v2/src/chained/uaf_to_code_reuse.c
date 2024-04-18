/*  Benchmark: Use After Free on function pointer leads to code reuse attack
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
#include <stdlib.h>

struct s_user {
    void (*func_ptr)(void);
    char username[8];
};

int count = 0;

void print_count() {
    printf("Count: %d\n", count);
}

void gadget(void) {
    printf("Test Failed: UAF to Code Reuse\n\n");
    exit(0);
}

int main(void) {
    printf("Starting test: UAF to Code Reuse\n");

    struct s_user *user = (struct s_user *)malloc(sizeof(struct s_user));
    count++;

    user->func_ptr = &print_count;
    strcpy(user->username, "Hedwig");

    user->func_ptr();

    // Free the struct object
    free(user);
    count--;

    // Realloc same buffer to long value
    unsigned long *value = (unsigned long *)malloc(sizeof(unsigned long));
    
    // Simulated user input: Address to code segment to be reused
    *value = (unsigned long)&gadget;

    // Use after free
    user->func_ptr();

    printf("Test Complete: UAF to Code Reuse\n\n");

}
