LIB_DIR    := lib
DEMO_DIR   := demo


LIB_SRCDIR    := $(LIB_DIR)/src
LIB_INCLDIR   := $(LIB_DIR)/include
LIB_BINDIR    := $(LIB_DIR)/bin

DEMO_SRCDIR    := $(DEMO_DIR)/src
DEMO_INCLDIR   := $(DEMO_DIR)/src
DEMO_BINDIR    := $(DEMO_DIR)/bin


LIB_HDR  := $(LIB_INCLDIR)/MPint.hpp

LIB_SRC  := $(LIB_SRCDIR)/MPint.cpp
LIB_OBJ  := $(LIB_BINDIR)/MPint.o
LIBRARY  := $(LIB_BINDIR)/libMP.a

LIB_WRAPPEDNATIVE_SRC  := $(LIB_SRCDIR)/MPintWrappedNative.cpp
LIB_WRAPPEDNATIVE_OBJ  := $(LIB_BINDIR)/MPintWrappedNative.o
LIBRARY_WRAPPEDNATIVE  := $(LIB_BINDIR)/libMPWrappedNative.a

DEMO_SRCS := $(DEMO_SRCDIR)/demo.cpp $(DEMO_SRCDIR)/exprTest.cpp
DEMO_HDRS := $(DEMO_INCLDIR)/demoTypedef.hpp $(DEMO_INCLDIR)/exprTest.hpp


TARGET_MP              := $(DEMO_BINDIR)/demoMP
TARGET_NATIVE          := $(DEMO_BINDIR)/demoNative
TARGET_WRAPPEDNATIVE   := $(DEMO_BINDIR)/demoWrappedNative


CXX      := g++
CXXFLAGS := -std=c++14 -Wall -Wextra -pedantic -Werror -O2 -flto=auto
AR       := ar
ARFLAGS  := rcs


.PHONY: all clean

all: $(TARGET_MP) $(TARGET_NATIVE) $(TARGET_WRAPPEDNATIVE)

clean:
	$(RM) $(TARGET_MP) $(TARGET_NATIVE) $(TARGET_WRAPPEDNATIVE) $(LIBRARY) $(LIBRARY_WRAPPEDNATIVE) $(LIB_OBJ) $(LIB_WRAPPEDNATIVE_OBJ)


$(LIB_OBJ): $(LIB_SRC) $(LIB_HDR)
	$(CXX) $(CXXFLAGS) -I$(LIB_INCLDIR) -c -o $@ $<

$(LIB_WRAPPEDNATIVE_OBJ): $(LIB_WRAPPEDNATIVE_SRC) $(LIB_HDR)
	$(CXX) $(CXXFLAGS) -I$(LIB_INCLDIR) -c -o $@ $<


$(LIBRARY): $(LIB_OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(LIBRARY_WRAPPEDNATIVE): $(LIB_WRAPPEDNATIVE_OBJ)
	$(AR) $(ARFLAGS) $@ $^

# when used as a starting point for a multiprecision implementation, MPint.cpp is identical to 
# MPintWrappedNative.cpp which just uses ordinary signed long int. At this stage, the resulting
# demoMP executable would fail assertions when it was compiled with -DDEMO_ARBPREC.
# As soon as you have true multi precision integers implemented in MPint.cpp, in particular the
# string constructors, you should switch on -DDEMO_ARBPREC as in the out-commented target below.
#$(TARGET_MP): $(DEMO_SRCS) $(DEMO_HDRS) $(LIBRARY)
#	$(CXX) $(CXXFLAGS) -DDEMO_ARBPREC -I$(LIB_INCLDIR) -I$(DEMO_INCLDIR) -o $@ $(DEMO_SRCS) -L$(LIB_BINDIR) -lMP
$(TARGET_MP): $(DEMO_SRCS) $(DEMO_HDRS) $(LIBRARY)
	$(CXX) $(CXXFLAGS) -I$(LIB_INCLDIR) -I$(DEMO_INCLDIR) -o $@ $(DEMO_SRCS) -L$(LIB_BINDIR) -lMP

$(TARGET_NATIVE): $(DEMO_SRCS) $(DEMO_HDRS)
	$(CXX) $(CXXFLAGS) -DDEMO_NATIVE -I$(DEMO_INCLDIR) -o $@ $(DEMO_SRCS)

$(TARGET_WRAPPEDNATIVE): $(DEMO_SRCS) $(DEMO_HDRS) $(LIBRARY_WRAPPEDNATIVE)
	$(CXX) $(CXXFLAGS) -I$(LIB_INCLDIR) -I$(DEMO_INCLDIR) -o $@ $(DEMO_SRCS) -L$(LIB_BINDIR) -lMPWrappedNative
