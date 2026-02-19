CXX      := g++
CXXFLAGS := -std=c++14 -Wall -Wextra -pedantic -Werror -Isrc
SRCDIR   := src
BINDIR   := bin

SRCS     := $(SRCDIR)/MPint.cpp $(SRCDIR)/demo.cpp
TARGET   := $(BINDIR)/demo

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS) $(SRCDIR)/MPint.hpp
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS)

clean:
	$(RM) $(TARGET)
