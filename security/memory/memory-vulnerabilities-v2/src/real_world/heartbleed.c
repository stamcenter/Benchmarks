/*  Benchmark: HeartBleed - Out-of-Bounds Read with length input
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
#include <stdlib.h>
#include <string.h>

int main() {

  printf("Starting test: HeartBleed Example\n");
  
  int test_status = 1;

  // Simulate input heartbeat request
  char *hb_input     = (char *)malloc(6);
  strcpy(hb_input, "HB MSG");

  // Sensitive information stored in memory
  char *rsa_key    = (char *)malloc(7);
  strcpy(rsa_key, "RSA KEY");

  int offset = rsa_key-hb_input;


  //Simulate user input with len greater than provided characters
  int num = 6 + offset + 7;

  printf("Responding to heartbeat request with %d characters:\n", num);
  for(int i=0;i<num;i++) {
    printf("%c", hb_input[i]);

    if(i>(6+offset) && hb_input[i] == rsa_key[i-offset])
      test_status = 0;

  }
  printf("\n");  

  if(test_status == 0)
    printf("Test Failed: HeartBleed\n\n");

  return 0;
}
