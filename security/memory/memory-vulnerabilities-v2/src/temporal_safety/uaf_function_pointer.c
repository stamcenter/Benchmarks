/*  Benchmark: Use After Free
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

/*  This vulnerability demonstrates a use after free vulnerability using function 
    pointers. It involves freeing the function pointer and then modifying the value
    using a different pointer in order to switch control to a target function.
*/


#include <stdio.h>
#include <stdlib.h>

typedef void (*fp)();


void default_function();
void target_function();

void main()
{
        fp *default_func_pointer = malloc(sizeof(fp));

        *default_func_pointer = default_function;
        (*default_func_pointer)();

        free(default_func_pointer); //pointer freed

        fp *target_func_pointer = malloc(sizeof(fp));
        *target_func_pointer = target_function;

        printf("Using default pointer after free\n");

        (*default_func_pointer)(); //use after free
}

void default_function(){
        printf("Public data\n");
}
void target_function(){
        printf("Test Failed: Use After Free for function pointer\n");
}