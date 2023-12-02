/*  Benchmark: Null Pointer Dereference
 *  @author  : Secure, Trusted, and Assured Microelectronics (STAM) Center

 *  Copyright (c) 2023 Trireme (STAM/SCAI/ASU)
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

int main() {

  printf("Starting test: Null pointer dereference\n");

  char *complete = "Hello World!";
  char *bad_ptr;

  bad_ptr = complete;

  printf("Printing hex characters of known string:\n");
  for(int i=0;i<12;i++) {
          printf("%x", bad_ptr[i]);
  }
  printf("%c", '\n');

  bad_ptr = NULL;

  printf("Printing hex characters of NULL string:\n");
  for(int i=0;i<12;i++) {
         printf("%x", bad_ptr[i]); 
  }

  printf("%c", '\n');

  printf("Test Failed: Null pointer dereference\n\n");

  return 0;
}
