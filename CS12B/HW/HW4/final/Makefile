
# @author John Allard
# @file   Makefile
# @info   This file will build my cyoa program given that all of the other requried source files are in the same directory.
# 		  Written for CS12B Assignment #4 at UCSC.

PROGRAM = cyoa

CXXSOURCES = main.cpp	   # list of source files
CXXOBJECTS = $(CXXSOURCES:.cpp=.o)  # expands to list of object files
CXXFLAGS = -std=c++11 $(INCLUDEDIRS)
CXX = g++

LDFLAGS = $(LIBDIRS) $(LIBS)

all: $(PROGRAM)

$(PROGRAM): $(CXXOBJECTS)
	$(CXX) -o $@ $(CXXOBJECTS) $(LDFLAGS)

clean:
	$(RM) -f $(CXXOBJECTS) $(PROGRAM)

run:
		  ./$(PROGRAM) 
