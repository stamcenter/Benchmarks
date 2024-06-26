@author  : Secure, Trusted, and Assured Microelectronics (STAM) Center

Copyright (c) 2024 Memory Safety Benchmarks (STAM/SCAI/ASU)
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.


# Memory Vulnerability Assessment Benchmark Suite

* This test suite includes programs to identify and simulate various memory safety issues.

## Directory Structure
```
|- README
|- Makefile
|- src
    |- basic
        |- oob_write.c
        |- null_ptr_dereference.c
        |- use_after_free.c
        |- oob_read.c
        |- free_not_at_start.c
        |- double_free.c
        |- free_not_on_heap.c
|- binaries
|- logs
```
## Usage
### Running Testsuite
The testsuite can be run using
```bash
make r_all
```

This will compile and run all tests, and report the results in command line.  
The complete log will be available in the run directory as `run.log`. Logs for individual runs can be found in the `logs` directory.  

To compile all tests without running, use 
```bash
make c_all
```


