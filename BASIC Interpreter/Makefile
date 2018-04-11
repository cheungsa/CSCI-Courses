CXX=g++
CXXFLAGS=-g -Wall -std=c++11

OBJS=hw5.o ArithmeticExpression.o BooleanExpression.o Command.o 

all: hw5

hw5: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)

hw5.o: hw5.cpp ArithmeticExpression.h BooleanExpression.h Command.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c hw5.cpp

ArithmeticExpression.o: ArithmeticExpression.cpp ArithmeticExpression.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c ArithmeticExpression.cpp

BooleanExpression.o: BooleanExpression.cpp BooleanExpression.h ArithmeticExpression.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c BooleanExpression.cpp

Command.o: Command.cpp Command.h BooleanExpression.h ArithmeticExpression.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c Command.cpp

.PHONY: clean

clean:
	rm -f *.o hw5