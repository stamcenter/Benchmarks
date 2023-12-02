/*  Benchmark: Free Not at Start of Buffer
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
#include <stdlib.h>

int main() {

  printf("Starting Test: Free not at start\n");

  char *complete  = malloc(sizeof(char) * 83);	
  strcpy(complete, "Hello World!Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod");


  printf("Printing characters of string before free:\n");
  for(int i=0;i<83;i++) {
          printf("%c", complete[i]);
  }
  printf("\n");

  free(complete+8);

  printf("Printing characters of string after free:\n");
  for(int i=0;i<83;i++) {
         printf("%c", complete[i]); 
  }

  printf("\n");

  printf("Test Failed: Free not at start\n\n");

  return 0;
}
