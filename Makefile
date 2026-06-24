LIB_DIR    := lib
DEMO_DIR   := demo


LIB_SRCDIR    := $(LIB_DIR)/src
LIB_INCLDIR   := $(LIB_DIR)/include
LIB_BINDIR    := $(LIB_DIR)/bin

DEMO_SRCDIR    := $(DEMO_DIR)/src
DEMO_INCLDIR   := $(DEMO_DIR)/src
DEMO_BINDIR    := $(DEMO_DIR)/bin


LIB_HDR  := $(LIB_INCLDIR)/MPint.hpp

LIB_GMP_SRC  := $(LIB_SRCDIR)/MPintGMP.cpp
LIB_GMP_OBJ  := $(LIB_BINDIR)/MPintGMP.o
LIBRARY_GMP  := $(LIB_BINDIR)/libMPGMP.a

LIB_WRAPPEDNATIVE_SRC  := $(LIB_SRCDIR)/MPintWrappedNative.cpp
LIB_WRAPPEDNATIVE_OBJ  := $(LIB_BINDIR)/MPintWrappedNative.o
LIBRARY_WRAPPEDNATIVE  := $(LIB_BINDIR)/libMPWrappedNative.a

DEMO_SRCS := $(DEMO_SRCDIR)/demo.cpp $(DEMO_SRCDIR)/exprTest.cpp $(DEMO_SRCDIR)/det.cpp $(DEMO_SRCDIR)/redu.cpp $(DEMO_SRCDIR)/demoUtils.cpp
DEMO_HDRS := $(DEMO_INCLDIR)/det.hpp $(DEMO_INCLDIR)/redu.hpp $(DEMO_INCLDIR)/demoUtils.hpp $(DEMO_INCLDIR)/demoTypedef.hpp $(DEMO_INCLDIR)/exprTest.hpp


TARGET_GMP             := $(DEMO_BINDIR)/demoGMP
TARGET_NATIVE          := $(DEMO_BINDIR)/demoNative
TARGET_WRAPPEDNATIVE   := $(DEMO_BINDIR)/demoWrappedNative


DIST_DIR         := dist/multiPrecOperators
DIST_LIB_SRCDIR  := $(DIST_DIR)/lib/src
DIST_LIB_INCLDIR := $(DIST_DIR)/lib/include
DIST_DEMO_SRCDIR := $(DIST_DIR)/demo/src

DIST_FILES := \
  $(DIST_LIB_SRCDIR)/MPint.cpp \
  $(DIST_LIB_SRCDIR)/MPintWrappedNative.cpp \
  $(DIST_LIB_INCLDIR)/MPint.hpp \
  $(DIST_DEMO_SRCDIR)/demoTypedef.hpp \
  $(DIST_DEMO_SRCDIR)/exprTest.cpp \
  $(DIST_DEMO_SRCDIR)/exprTest.hpp


CXX      := g++
CXXFLAGS := -std=c++14 -Wall -Wextra -pedantic -Werror -O2 -flto=auto
AR       := ar
ARFLAGS  := rcs


.PHONY: all clean

all: $(TARGET_WRAPPEDNATIVE) $(TARGET_GMP) $(TARGET_NATIVE) $(DIST_FILES)

clean:
	$(RM) $(TARGET_WRAPPEDNATIVE) $(LIBRARY_WRAPPEDNATIVE) $(LIB_WRAPPEDNATIVE_OBJ) $(TARGET_GMP) $(TARGET_NATIVE) $(LIBRARY_GMP) $(LIB_GMP_OBJ)
	$(RM) $(DIST_FILES)


$(LIB_WRAPPEDNATIVE_OBJ): $(LIB_WRAPPEDNATIVE_SRC) $(LIB_HDR)
	$(CXX) $(CXXFLAGS) -I$(LIB_INCLDIR) -c -o $@ $<

$(LIB_GMP_OBJ): $(LIB_GMP_SRC) $(LIB_HDR)
	$(CXX) $(CXXFLAGS) -I$(LIB_INCLDIR) -c -o $@ $<


$(LIBRARY_WRAPPEDNATIVE): $(LIB_WRAPPEDNATIVE_OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(LIBRARY_GMP): $(LIB_GMP_OBJ)
	$(AR) $(ARFLAGS) $@ $^


$(TARGET_WRAPPEDNATIVE): $(DEMO_SRCS) $(DEMO_HDRS) $(LIBRARY_WRAPPEDNATIVE) $(LIB_HDR)
	$(CXX) $(CXXFLAGS) -I$(DEMO_INCLDIR) -I$(LIB_INCLDIR) -o $@ $(DEMO_SRCS) -L$(LIB_BINDIR) -lMPWrappedNative

$(TARGET_GMP): $(DEMO_SRCS) $(DEMO_HDRS) $(LIBRARY_GMP) $(LIB_HDR)
	$(CXX) $(CXXFLAGS) -DDEMO_ARBPREC -I$(DEMO_INCLDIR) -I$(LIB_INCLDIR) -o $@ $(DEMO_SRCS) -L$(LIB_BINDIR) -lMPGMP -lgmp

$(TARGET_NATIVE): $(DEMO_SRCS) $(DEMO_HDRS)
	$(CXX) $(CXXFLAGS) -DDEMO_NATIVE -I$(DEMO_INCLDIR) -o $@ $(DEMO_SRCS)


$(DIST_LIB_SRCDIR)/MPint.cpp: $(LIB_WRAPPEDNATIVE_SRC)
	cp $< $@

$(DIST_LIB_SRCDIR)/MPintWrappedNative.cpp: $(LIB_WRAPPEDNATIVE_SRC)
	cp $< $@

$(DIST_LIB_INCLDIR)/MPint.hpp: $(LIB_HDR)
	cp $< $@

$(DIST_DEMO_SRCDIR)/demoTypedef.hpp: $(DEMO_SRCDIR)/demoTypedef.hpp
	cp $< $@

$(DIST_DEMO_SRCDIR)/exprTest.cpp: $(DEMO_SRCDIR)/exprTest.cpp
	cp $< $@

$(DIST_DEMO_SRCDIR)/exprTest.hpp: $(DEMO_SRCDIR)/exprTest.hpp
	cp $< $@
