#  Description: Makefile for Memory Vulnerability Benchmark Testsuite
#  @author  : Secure, Trusted, and Assured Microelectronics (STAM) Center
# 
#  Copyright (c) 2023 Trireme (STAM/SCAI/ASU)
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#  The above copyright notice and this permission notice shall be included in
#  all copies or substantial portions of the Software.
# 
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#  THE SOFTWARE.
# 


# Variables
CC = gcc
BIN_DIR = binaries
SRC_DIR = src
LOG_DIR = logs

# Override in command line using make TARGET_ARCH=riscv to use riscv
TARGET_ARCH = x86

# Check if the architecture is set to riscv
ifeq ($(TARGET_ARCH), riscv)
    CC = riscv64-unknown-elf-gcc
    QEMU_CMD = qemu-riscv64
endif

# Get all C files in SRC_DIR
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
BIN_FILES := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%,$(SRC_FILES))

# Compilation rules
$(BIN_DIR)/%: $(SRC_DIR)/%.c
	@mkdir -p $(BIN_DIR)
	@$(CC) -o $@ $<

# Compile individual C files
c_%: $(SRC_DIR)/%.c
	$(CC) -o $(BIN_DIR)/$(notdir $(basename $<)) $<

# Run rules
r_%: $(BIN_DIR)/%
	@mkdir -p $(LOG_DIR)
	@echo "\n************************************************************\n" >$(LOG_DIR)/$*.log
	@echo "Running $*"
ifeq ($(TARGET_ARCH), riscv)
	@stdbuf -o0 $(QEMU_CMD) $< >> $(LOG_DIR)/$*.log 2>&1 || true
else
	@stdbuf -o0 $< >> $(LOG_DIR)/$*.log 2>&1 || true
endif
	@cat $(LOG_DIR)/$*.log >> run.log

# c_all target to compile all C files
c_all: $(BIN_FILES)

# r_all target to run all compiled files
r_all: clean $(patsubst $(BIN_DIR)/%,r_%,$(BIN_FILES))
	@failed_runs=`grep -a "Test Failed" run.log | wc -l`;\
	total_runs=$(words $(BIN_FILES)); \
	percentage=$$((failed_runs * 100 / total_runs)); \
	echo "\nFound failures in $$failed_runs out of $$total_runs ($$percentage%) tests\nCheck run.log for details"

# Clean rule
clean:
	@-rm -rf $(BIN_DIR)
	@-rm -rf $(LOG_DIR)
	@-rm run.log
