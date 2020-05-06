TARGET = FinalProject
LIBS = -lm #Math Library, just a placeholder
HEADERS = Node.h EdgeNode.h WeightedGraph.h 
SRCS = FinalProject.cpp Node.cpp EdgeNode.cpp WeightedGraph.cpp
OBJECTS := $(patsubst %.cpp,%.o,$(SRCS))
CXX = g++
CXX_FLAGS = -Wall -g -std=c++11 -chrono

.PHONY: default all clean

all: depend $(TARGET)

#Rules to recompile template headers when they change
depend: .depend
.depend: $(HEADERS)
	rm -f ./.depend
	$(CXX) $(CXX_FLAGS) -MM $^ > ./.depend;
include .depend

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $(OBJECTS) $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f ./.depend
	-rm -f $(TARGET)