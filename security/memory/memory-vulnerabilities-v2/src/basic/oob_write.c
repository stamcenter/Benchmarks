/*  Benchmark: Out-of-Bounds Write
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

int main() {

  printf("Starting Test: OOB Write\n");

  int test_status = 1;

  char *public  = malloc(sizeof(char) * 5);	
  strcpy(public, "FIRST");

  char *private = malloc(sizeof(char) * 6);
  strcpy(private, "SECOND");

  int offset = private-public;

  printf("Updating value of first string with ?. \n");
  printf("Original value: %s\n", public);
  for(int i=0;i<5;i++) {
	  public[i] = '?';
  }
  printf("New value: %s\n", public);

  printf("Updating value of second string with ? from first string pointer\n");
  printf("Original value: %s\n", private);
  for(int i=0;i<6;i++) {
	  public[i+offset] = '?';
	  if(private[i] == '?')
	    test_status = 0;
  }
  printf("New value: %s\n", private);

  if(test_status == 0)
    printf("Test Failed: OOB Write\n\n");

  return 0;
}
