# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Source files and output executable name
SRC = Book.cpp Library.cpp Main.cpp 
OUT = LibraryManager

# Default target: build the executable
all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Clean target: remove the executable and any object files
clean:
	del $(OUT).exe

.PHONY: all clean