CXX = c++
ARCH = -arch arm64
CXXFLAGS = $(ARCH) -std=c++17 -Wall -Wextra -pthread \
           -I/opt/homebrew/opt/googletest/include

LDFLAGS = $(ARCH) -L/opt/homebrew/opt/googletest/lib -lgtest -lgtest_main -pthread

# App source files
APP_SRCS = main.cpp Job.cpp ThreadPool.cpp JobScheduler.cpp
APP_OBJS = $(APP_SRCS:.cpp=.o)

# Test-specific source files (no main.cpp!)
TEST_SRCS = test_job_scheduler.cpp Job.cpp ThreadPool.cpp JobScheduler.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

TARGET = job_scheduler
TEST_TARGET = test_runner

all: $(TARGET)

$(TARGET): $(APP_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $^ $(LDFLAGS)

clean:
	rm -f *.o $(TARGET) $(TEST_TARGET)

.PHONY: all clean test
