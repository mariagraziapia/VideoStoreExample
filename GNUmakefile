# ---- Makefile for VideoStore refactoring example ----
# Initial version: M.G. Pia, June 2014
# Extended version: S. Kluth, September 2014
# Adapted (removed use of Boost Test): M.G. Pia, January 2014

CXX        = g++
LD         = g++
OPT        = -g
CXXFLAGS   = -Wall $(OPT) 
LDFLAGS    =
SOURCES    = Customer.cc Movie.cc Rental.cc
TESTSRC    = testVideoStore.cc
OBJECTS    = $(SOURCES:.cc=.o) $(TESTSRC:.cc=.o)
EXECUTABLE = $(basename $(TESTSRC) )

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(LD) $(LDFLAGS) -o $@ $^ 
	./$@ 

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

