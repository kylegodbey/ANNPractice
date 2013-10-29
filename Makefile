# Makefile for Assignment 02
# Suzanne Dazo and Kyle Godbey

#------------------------------------------------------------------#

Program: main.o ProcElem.o ANN.o
	g++ main.o ProcElem.o ANN.o -o Program

main.o:	main.cc ProcElem.h ANN.h
	g++ -c main.cc
ProcElem.o: ProcElem.cc ProcElem.h
	g++ -c ProcElem.cc
ANN.o: ANN.cc ANN.h
	g++ -c ANN.cc

#------------------------------------------------------------------#

# Rule to clean up the directory
clean:	
	rm -f *~ .*~ *.o *.gch core* Program
