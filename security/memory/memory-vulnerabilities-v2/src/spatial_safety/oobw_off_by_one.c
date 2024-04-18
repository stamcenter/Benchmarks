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

/*  This vulnerability demonstrates an out of bounds write. It consists of an off-by-one
    error when setting values in a multi-dimensional array.
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    int mat[3][3] = {{0,0,0},
                     {0,0,0},
                     {0,0,0}};
    
    int test_status = 0;

    // incorrectly setting values in an array
    for(int i=0;i<=3;i++){
        for(int j=0;j<=3;j++){
            mat[i][j] = (i*3)+j +1;
            if((i>2 || j>2) && mat[i][j] == (i*3)+j +1)
                test_status = 1;
        }
    }

    for(int i=0;i<=3;i++){
        for(int j=0;j<=3;j++){
            printf("%d ", mat[i][j]); 
        }
        printf("\n");
    }
    if(test_status == 1)
        printf("Test Failed: Off by one in integer matrix manipulation leads to Out of Bounds Write\n");
    
}