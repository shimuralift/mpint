CXX      := g++
CXXFLAGS := -std=c++14 -Wall -Wextra -pedantic -Werror -Isrc
AR       := ar
ARFLAGS  := rcs
SRCDIR   := src
BINDIR   := bin

LIB_SRC  := $(SRCDIR)/MPint.cpp
LIB_HDR  := $(SRCDIR)/MPint.hpp
LIB_OBJ  := $(BINDIR)/MPint.o
LIBRARY  := $(BINDIR)/libMP.a

DEMO_SRCS := $(SRCDIR)/demo.cpp $(SRCDIR)/det.cpp
DEMO_HDRS := $(SRCDIR)/MPint.hpp $(SRCDIR)/det.hpp
TARGET   := $(BINDIR)/demo

.PHONY: all clean

all: $(TARGET)

$(LIB_OBJ): $(LIB_SRC) $(LIB_HDR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(LIBRARY): $(LIB_OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(TARGET): $(DEMO_SRCS) $(DEMO_HDRS) $(LIBRARY)
	$(CXX) $(CXXFLAGS) -o $@ $(DEMO_SRCS) -L$(BINDIR) -lMP

clean:
	$(RM) $(TARGET) $(LIBRARY) $(LIB_OBJ)
