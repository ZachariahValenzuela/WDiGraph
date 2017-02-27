# Makefile for WDiGraph class and program driver - Jeff Braun

#Macros to specify compiler, compiler/linking flags, target file
C++  = c++ -std=c++11
CFLAGS = -g -Wall 
LD = c++
LDFLAGS =
LIBS =
OBJS = Driver.o WDiGraph.o 
EXEC = Driver

#Rules to create target file Driver
# If any files right of the colon are modified, then recompile the object file
$(EXEC):	$(OBJS)
		$(LD) $(LDFLAGS) -o $(EXEC) $(OBJS) $(LIBS)

WDiGraph.o:	WDiGraphInterface.h WDiGraph.h WDiGraph.cpp WGraphNode.h WGraphNode.cpp
		$(C++) $(CFLAGS) -c WDiGraph.cpp

Driver.o:	Driver.cpp WDiGraph.o 
		$(C++) $(CFLAGS) -c Driver.cpp

clean:
		rm -f $(OBJS) $(EXEC)

#rule to submit progam when completed
submit:
		rm -f $(OBJS) $(EXEC)
		tar cvzf ../`whoami`3.tgz ../$(shell basename $(CURDIR))/*
		mail -a ../`whoami`3.tgz -s Program3   jbraun@mtech.edu < /dev/null

