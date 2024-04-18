/*  Benchmark: Heap Buffer Overflow
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

/* This vulnerability showcases a heap buffer overflow, wherein data from one allocated memory chunk is
 * utilized to overwrite a buffer located immediately after it within the heap memory space. In this exploit,
 * careful management of the data preceding the targeted buffer is maintained to prevent corruption of the
 * victim chunk's metadata. This ensures that even after corruption of the data, the metadata would be intact to
 * allow for a call to free on the chunk. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocating two buffers
    char *a = malloc(0x20);  // 32 bytes
    char *b = malloc(0x20);  // 32 bytes

    char first_char_of_b = b[0];

    // Filling the buffer 'b' with initial data
    strcpy(b, "1234567890123456");

    // Printing original content of 'b'
    printf("Original content of b: %s\n", b);

    // Calculating the distance to reach just before 'b's content
    size_t distance = (size_t) (b - a) - 16; // 16 bytes for metadata

    // Creating auxiliary buffer to form the overflow data
    char *overflowData = (char *) malloc(distance + 0x10 + 0x02); // Additional space for 'b' and null-terminator
    memset(overflowData, 'A', distance); // Filling up to 'b'
    memcpy(overflowData + distance, a + distance, 0x10 + 0x02); // Overflow content for 'b'
    memset(overflowData + distance + 16, 'B', 2); // Overflow content for 'b'

    // Copying the formed data into 'a', causing overflow into 'b'
    memcpy(a, overflowData, distance + 16 + 2);

    for (int i = 0; i < distance + 16 + 2; i++) {
        printf("%c", a[i]);
    }

    printf("\n");
    // Printing the altered content of 'b'
    printf("Content of b after overflow: %s\n", b);

    if (first_char_of_b != b[0]) {
        printf("Test Failed: Heap buffer overflow occured\n");
    }


    // Cleanup
    free(a);
    free(b);
    free(overflowData);

    return 0;
}
