CXX = c++
ARCH = -arch arm64
CXXFLAGS = $(ARCH) -std=c++17 -Wall -Wextra -pthread \
           -I/opt/homebrew/opt/googletest/include

LDFLAGS = $(ARCH) -L/opt/homebrew/opt/googletest/lib -lgtest -lgtest_main -pthread

# Define the directories for the source files
SRC_DIR = src
TEST_DIR = test

# App source files
APP_SRCS = ${SRC_DIR}/main.cpp ${SRC_DIR}/Job.cpp ${SRC_DIR}/ThreadPool.cpp ${SRC_DIR}/JobScheduler.cpp
APP_OBJS = $(APP_SRCS:.cpp=.o)

# Test-specific source files (no main.cpp!)
TEST_SRCS = ${TEST_DIR}/test_job_scheduler.cpp ${SRC_DIR}/Job.cpp ${SRC_DIR}/ThreadPool.cpp ${SRC_DIR}/JobScheduler.cpp
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
	rm -f ${TEST_DIR}/*.o ${SRC_DIR}/*.o $(TARGET) $(TEST_TARGET)

.PHONY: all clean test
