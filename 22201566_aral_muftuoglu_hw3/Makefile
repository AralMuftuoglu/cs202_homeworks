CXX = g++
CXXFLAGS = -Wall -g -std=c++17
GTEST_FLAGS = -lgtest -lgtest_main -pthread

TARGET = test
SRCS = HashTable.cpp HashTableImproved.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(GTEST_FLAGS)

HashTable.o: HashTable.cpp HashTable.h
	$(CXX) $(CXXFLAGS) -c HashTable.cpp -o HashTable.o

HashTableImproved.o: HashTableImproved.cpp HashTableImproved.h
	$(CXX) $(CXXFLAGS) -c HashTableImproved.cpp -o HashTableImproved.o

clean:
	rm -f $(TARGET) $(OBJS)
