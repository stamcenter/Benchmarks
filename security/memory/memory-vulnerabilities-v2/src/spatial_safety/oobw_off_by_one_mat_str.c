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

/*  This vulnerability demonstrates an out of bounds read. It consists of an off-by-one
    error when printing out a multi-dimensional array.
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    char mat[3][3] = {"abc","def","ghi"};

    char mat2[3][3] = {"jkl","mno","pqr"};

    int test_status = 0;
    
    // incorrectly printing out array
    // Max index of array should be mat[2][2] but loop goes up to 3
    for(int i=0;i<=3;i++){
        for(int j=0;j<=3;j++){
            mat[i][j] = 'x';
        }
        printf("\n");
    }
    
    printf("Printing mat 1\n");

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("%c", mat[i][j]);
        }
        printf("\n");
    }

    printf("Printing mat 2\n");

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("%c", mat2[i][j]);
            if(mat2[i][j] == 'x')
                test_status = 1;
        }
        printf("\n");
    }

    if(test_status == 1)
        printf("Test Failed: Off by One in string matrix manipulation leads to Out of Bounds Write\n");
    
}