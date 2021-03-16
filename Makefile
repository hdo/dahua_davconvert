CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -Wall -std=c++11
LDFLAGS=-g -Wall -std=c++11
LDLIBS=-L./lib -ldhplay
INCLUDES=-I. -I./lib


SRCS=davconvert.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: davconvert

davconvert: $(OBJS)
	$(CXX) $(LDFLAGS) $(INCLUDES) -o davconvert $(OBJS) $(LDLIBS) 

davconvert.o: davconvert.cpp

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) davconvert
