CXX      := g++
CXXFLAGS := -std=c++14 -Wall -Wextra -pedantic -Werror -Isrc
SRCDIR   := src
BINDIR   := bin

SRCS     := $(SRCDIR)/MPint.cpp $(SRCDIR)/demo.cpp $(SRCDIR)/det.cpp
HDRS     := $(SRCDIR)/MPint.hpp $(SRCDIR)/det.hpp
TARGET   := $(BINDIR)/demo

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS)

clean:
	$(RM) $(TARGET)
