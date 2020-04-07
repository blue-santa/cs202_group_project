TARGET = prog 
SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h*)
OBJECTS = $(SOURCES:%.cpp=%.o)
LD = g++
CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -Wfatal-errors -Iinclude -DGL_SILENCE_DEPRECATION -I.
LDFLAGS = 

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) src/*.o
	$(RM) $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

