# Compiler and flags
CXX = c++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread

# Source files
SRCS = main.cpp Job.cpp ThreadPool.cpp JobScheduler.cpp
OBJS = $(SRCS:.cpp=.o)

# Output binary name
TARGET = job_scheduler

# Default rule
all: $(TARGET)

# Link object files into final binary
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each .cpp file into a .o file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
