/*  Benchmark: Out-of-Bounds Read
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
#include <stdlib.h>
#include <string.h>

int main() {

  printf("Starting test: OOB Read\n");
  
  int test_status = 1;

  char *public     = (char *)malloc(6);
  strcpy(public, "public");

  char *private    = (char *)malloc(14);
  strcpy(private, "secretpassword");

  int offset = private-public;
//  printf("Offset of private array w.r.t public array: %d\n", offset);

  
  printf("Printing characters of public array\n");
  for(int i=0;i<6;i++) {
          printf("%c", public[i]);
  }
  printf("\n");

  printf("Printing characters of private array from public array\n");
  for(int i=0;i<14;i++) {
          printf("%c", public[i+offset]);
	  if(public[i+offset] == private[i])
	    test_status = 0;
  }
  printf("\n");

  if(test_status == 0)
    printf("Test Failed: OOB Read\n\n");

  return 0;
}
