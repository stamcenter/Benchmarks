#  Description: Makefile for Memory Vulnerability Benchmark Testsuite
#  @author  : Secure, Trusted, and Assured Microelectronics (STAM) Center
# 
#  Copyright (c) 2024 Memory Safety Benchmarks (STAM/SCAI/ASU)
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
TARGET_ARCH = x86  # Default target architecture

# Check if the architecture is set to riscv
ifeq ($(TARGET_ARCH), riscv)
	CC = riscv64-linux-gnu-gcc
	QEMU_CMD = qemu-riscv64
endif

# Directories containing C files
#SRC_SUBDIRS := spatial_safety control_flow_hijacking
SRC_SUBDIRS := basic  chained  control_flow_hijacking  real_world  spatial_safety temporal_safety
# Function to generate compilation rules for a given directory
define compile_rule
$(BIN_DIR)/$(1)/%: $(SRC_DIR)/$(1)/%.c
	@mkdir -p $$(dir $$@)
	@$(CC) -pthread -static -o $$@ $$<
endef

# Generate compilation rules for each directory
$(foreach dir,$(SRC_SUBDIRS),$(eval $(call compile_rule,$(dir))))

# Function to get all files in specific directories under SRC_DIR
define get_files
$(wildcard $(1)/*.c)
endef

# Get all C files in specific directories under SRC_DIR
EXISTING_SRC_FILES := $(foreach dir,$(SRC_SUBDIRS),$(call get_files,$(SRC_DIR)/$(dir)))
BIN_FILES := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%,$(EXISTING_SRC_FILES))


# Function to run a specific file in a directory
define run_specific_file
$(eval TARGET_FILE := $(patsubst $(SRC_DIR)/%,%,$(1)))
$(eval DIR_NAME := $(dir $(TARGET_FILE)))
$(eval FILE_NAME := $(notdir $(basename $(TARGET_FILE))))
$(eval TARGET_PATH := $(BIN_DIR)/$(DIR_NAME)$(FILE_NAME))

c_$(FILE_NAME): $(TARGET_PATH)

r_$(FILE_NAME): $(TARGET_PATH)
	@mkdir -p $(LOG_DIR)/$(DIR_NAME)
	@echo "\n************************************************************\n" >$(LOG_DIR)/$(DIR_NAME)/$$(notdir $$(basename $(TARGET_PATH))).log
	@echo "Running $$(notdir $$(basename $(TARGET_PATH)))"
	@echo "Running $$(notdir $$(basename $(TARGET_PATH)))\n" >> $(LOG_DIR)/$(DIR_NAME)/$$(notdir $$(basename $(TARGET_PATH))).log 
	@if [ "$(TARGET_ARCH)" = "riscv" ]; then \
		stdbuf -o0 $(QEMU_CMD) $$< >> $(LOG_DIR)/$(DIR_NAME)/$$(notdir $$(basename $(TARGET_PATH))).log 2>&1 || true; \
	else \
		stdbuf -o0 $$< >> $(LOG_DIR)/$(DIR_NAME)/$$(notdir $$(basename $(TARGET_PATH))).log 2>&1 || true; \
	fi
	@cat $(LOG_DIR)/$(DIR_NAME)/$$(notdir $$(basename $(TARGET_PATH))).log >> run.log
endef

# Generate run rules for any file in any directory that exists
$(foreach file,$(EXISTING_SRC_FILES),$(eval $(call run_specific_file,$(file))))

# Run all compiled files in specific directories
r_all: clean $(foreach file,$(EXISTING_SRC_FILES),r_$(notdir $(basename $(file))))
	@failed_runs=`grep -a "Test Failed" run.log | wc -l`;\
        total_runs=$(words $(BIN_FILES)); \
        percentage=$$((failed_runs * 100 / total_runs)); \
        echo "\nFound failures in $$failed_runs out of $$total_runs ($$percentage%) tests\nCheck run.log for details"

# Compile all files in sub directories
c_all: clean $(foreach file,$(EXISTING_SRC_FILES),c_$(notdir $(basename $(file))))


# Clean rule
clean:
	@-rm -rf $(BIN_DIR) $(LOG_DIR) run.log

