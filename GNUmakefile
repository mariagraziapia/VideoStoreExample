CXX        = g++
LD         = g++
OPT        = -g
CXXFLAGS   = -Wall $(OPT)
LDFLAGS    =
SOURCES    = Customer.cc Movie.cc 
TESTSRC    = testVideoStore.cc
OBJECTS    = $(SOURCES:.cc=.o) $(TESTSRC:.cc=.o)
EXECUTABLE = $(basename $(TESTSRC) )
BOOSTTESTOPT = --log_level=message

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(LD) $(LDFLAGS) -o $@ $^ -lboost_unit_test_framework 
	./$@ $(BOOSTTESTOPT)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

