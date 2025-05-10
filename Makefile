CXX = clang++
CXXFLAGS = -std=c++20 -Wall

# Target name
TARGET = mazer maze_tools

# Source files
SRCS = mazer.cpp maze_tools.cpp

# Default build
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Clean build
clean:
	rm -f $(TARGET)