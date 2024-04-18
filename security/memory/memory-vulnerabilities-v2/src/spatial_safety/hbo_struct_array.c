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


/* This vulnerability showcases a heap buffer overflow. It occurs when the program writes
 * beyond the allocated memory for an array, potentially corrupting adjacent memory regions. In this case, the
 * code calculates the distance between two arrays and exploits this knowledge to overwrite the data in the
 * second array, leading to unexpected behavior
 * */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    int id;
} Record;

int main() {
    Record *a = malloc(5 * sizeof(Record));
    Record *b = malloc(5 * sizeof(Record));

    // Set initial data for b
    for (int i = 0; i < 5; i++) {
        snprintf(b[i].name, 20, "Name%d", i);
        b[i].id = i;
    }

    // Inspect the content of b
    printf("b[0].name = %s, b[0].id = %d\n", b[0].name, b[0].id);

    // Calculate the distance from the last entry of 'a' to 'b'
    size_t distance = (size_t)((char *)b - ((char *)a + 4 * sizeof(Record))) - 16;
    char *overflowData = (char *)malloc(distance + sizeof(Record) + 16);

    // Fill the space up to b's metadata with 'A's
    memset(overflowData, 'A', distance);

    // Copy the metadata of b
    memcpy(overflowData + distance, (char *)b - 16, 16);

    // Prepare new record to overflow into b
    Record newRecord = {"aalkdaweouiadfkajdfkjafdkjafauweqaajh", 9999};
    memcpy(overflowData + distance + 16, &newRecord, sizeof(Record));

    // Perform the overflow starting from the last entry of 'a'
    memcpy((char *)a + 4 * sizeof(Record), overflowData, distance + sizeof(Record) + 16);

    // Inspect the content of b
    printf("b[0].name = %s, b[0].id = %d\n", b[0].name, b[0].id);

    // Now, compare b[0].name with "Name0"
    if (strcmp(b[0].name, "Name0") == 0) {
        printf("b[0].name is equal to \"Name0\".\n");
    } else {
        printf("Test Failed: b[0].name is not equal to \"Name0\".\n");
    }

    free(a);
    free(b);
    free(overflowData);

    return 0;
}

