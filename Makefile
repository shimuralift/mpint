SRCDIR   := src
BINDIR   := bin


LIB_HDR  := $(SRCDIR)/MPint.hpp

LIB_SRC  := $(SRCDIR)/MPint.cpp
LIB_OBJ  := $(BINDIR)/MPint.o
LIBRARY  := $(BINDIR)/libMP.a

LIBGMP_SRC  := $(SRCDIR)/MPintGMP.cpp
LIBGMP_OBJ  := $(BINDIR)/MPintGMP.o
LIBRARYGMP  := $(BINDIR)/libMPGMP.a


DEMO_SRCS := $(SRCDIR)/demo.cpp $(SRCDIR)/exprtest.cpp $(SRCDIR)/det.cpp $(SRCDIR)/redu.cpp $(SRCDIR)/demoUtils.cpp
DEMO_HDRS := $(SRCDIR)/det.hpp $(SRCDIR)/redu.hpp $(SRCDIR)/demoUtils.hpp


TARGET   := $(BINDIR)/demo

TARGETGMP   := $(BINDIR)/demoGMP

TARGETNATIVE   := $(BINDIR)/demoNative


CXX      := g++
CXXFLAGS := -std=c++14 -Wall -Wextra -pedantic -Werror -O2 -flto -I$(SRCDIR)
AR       := ar
ARFLAGS  := rcs


.PHONY: all clean

all: $(TARGET) $(TARGETGMP) $(TARGETNATIVE)


$(LIB_OBJ): $(LIB_SRC) $(LIB_HDR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<


$(LIBGMP_OBJ): $(LIBGMP_SRC) $(LIB_HDR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<


$(LIBRARY): $(LIB_OBJ)
	$(AR) $(ARFLAGS) $@ $^


$(LIBRARYGMP): $(LIBGMP_OBJ)
	$(AR) $(ARFLAGS) $@ $^


$(TARGET): $(DEMO_SRCS) $(DEMO_HDRS) $(LIBRARY)
	$(CXX) $(CXXFLAGS) -o $@ $(DEMO_SRCS) -L$(BINDIR) -lMP


$(TARGETGMP): $(DEMO_SRCS) $(DEMO_HDRS) $(LIBRARYGMP)
	$(CXX) $(CXXFLAGS) -DDEMO_GMP -o $@ $(DEMO_SRCS) -L$(BINDIR) -lMPGMP -lgmp

$(TARGETNATIVE): $(DEMO_SRCS) $(DEMO_HDRS)
	$(CXX) $(CXXFLAGS) -DDEMO_NATIVE -o $@ $(DEMO_SRCS)


clean:
	$(RM) $(TARGET) $(LIBRARY) $(LIB_OBJ) $(TARGETGMP) $(TARGETNATIVE) $(LIBRARYGMP) $(LIBGMP_OBJ)
