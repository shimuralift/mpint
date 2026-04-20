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


LIBGMP_SRC  := $(SRCDIR)/MPintGMP.cpp
LIBGMP_HDR  := $(SRCDIR)/MPintGMP.hpp
LIBGMP_OBJ  := $(BINDIR)/MPintGMP.o
LIBRARYGMP  := $(BINDIR)/libMPGMP.a


DEMO_SRCS := $(SRCDIR)/demo.cpp $(SRCDIR)/det.cpp
DEMO_HDRS := $(SRCDIR)/MPint.hpp $(SRCDIR)/det.hpp
TARGET   := $(BINDIR)/demo


DEMOGMP_SRCS := $(SRCDIR)/demo.cpp $(SRCDIR)/det.cpp
DEMOGMP_HDRS := $(SRCDIR)/MPintGMP.hpp $(SRCDIR)/det.hpp
TARGETGMP   := $(BINDIR)/demoGMP


.PHONY: all clean

all: $(TARGET) $(TARGETGMP)


$(LIB_OBJ): $(LIB_SRC) $(LIB_HDR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<


$(LIBGMP_OBJ): $(LIBGMP_SRC) $(LIBGMP_HDR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<


$(LIBRARY): $(LIB_OBJ)
	$(AR) $(ARFLAGS) $@ $^


$(LIBRARYGMP): $(LIBGMP_OBJ)
	$(AR) $(ARFLAGS) $@ $^


$(TARGET): $(DEMO_SRCS) $(DEMO_HDRS) $(LIBRARY)
	$(CXX) $(CXXFLAGS) -o $@ $(DEMO_SRCS) -L$(BINDIR) -lMP


$(TARGETGMP): $(DEMOGMP_SRCS) $(DEMOGMP_HDRS) $(LIBRARYGMP)
	$(CXX) $(CXXFLAGS) -o $@ $(DEMOGMP_SRCS) -L$(BINDIR) -lMPGMP -lgmp


clean:
	$(RM) $(TARGET) $(LIBRARY) $(LIB_OBJ) $(TARGETGMP) $(LIBRARYGMP) $(LIBGMP_OBJ)
