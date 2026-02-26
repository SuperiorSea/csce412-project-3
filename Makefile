CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
SRCS = main.cpp IPAddress.cpp Request.cpp RequestQueue.cpp WebServer.cpp LoadBalancer.cpp Switch.cpp SwitchConfig.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
