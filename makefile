CXX = g++

CXXFLAGS = -std=c++20 -O2 -Wall

SRC = kernel.cpp kernel_utils.cpp history.cpp

TARGET = kernel_program

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
