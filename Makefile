# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# SFML library location and linking flags
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files and output executable
SRCS = main.cpp Board.cpp Tile.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = monopoly

# Default rule to compile the program
all: $(TARGET)

# Rule to link the object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(SFML_LIBS)

# Rule to compile the source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: clean all
