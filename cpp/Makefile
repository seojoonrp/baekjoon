CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

F ?= test

SRC = $(F).cpp
TARGET = $(F)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)
	@echo "Compile success: $(SRC) -> $(TARGET)"

run: $(TARGET)
	./$(TARGET)

clean:
	@rm -f $(TARGET)
	@echo "Cleaned: $(TARGET)"