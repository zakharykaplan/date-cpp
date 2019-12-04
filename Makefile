# Root directory
ROOT ?= .

# Input directories
INCLUDE ?= $(ROOT)/include
SRC ?= $(ROOT)/src

# Build directories
BUILD ?= $(ROOT)/build
OBJ ?= $(BUILD)/obj

# Target executable
TARGET ?= $(BUILD)/$(shell basename $(PWD))

# Inputs
SRCS := $(wildcard $(SRC)/*.cpp)
OBJS := $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRCS))
INCLUDES := $(addprefix -I,$(INCLUDE))

# Compiler
CXX ?= g++
CXXFLAGS ?= -Wall -g -std=c++17 $(INCLUDES)

# Build
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p $(OBJ)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean
.PHONY: clean
clean:
	@rm -rfv $(TARGET) $(OBJS)

# Run
.PHONY: run
run: $(TARGET)
	@$(TARGET)
