CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I include

SOURCES = main.cpp \
          src/MediaItem.cpp \
          src/Book.cpp \
          src/Magazine.cpp \
          src/DVD.cpp \
          src/Library.cpp

OBJECTS = $(SOURCES:.cpp=.o)
TARGET = library

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
