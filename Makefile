CXX      := g++
CXXFLAGS := -std=c++14 -Wall -Wextra -pedantic -Werror -Isrc
SRCDIR   := src
BINDIR   := bin

SRCS     := $(SRCDIR)/MPint.cpp $(SRCDIR)/demo.cpp
TARGET   := $(BINDIR)/demo

.PHONY: all clean

all: $(TARGET)

$(BINDIR):
	mkdir -p $(BINDIR)

$(TARGET): $(SRCS) $(SRCDIR)/MPint.hpp | $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS)

clean:
	rm -rf $(BINDIR)
