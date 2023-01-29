#-----------------------
# Name: Ishaan Das      
# CruzID: isdas         
# Assignment Name: pa2
#-----------------------

#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 2
#
# make                   makes FindPath
# make GraphTest        makes GraphTest
# make clean             removes all binaries
# make checkTest       checks GraphTest for memory errors
# make checkFindPath          checks FindPath for memory errors
#------------------------------------------------------------------------------

FindPath : FindPath.o Graph.o List.o
	gcc -std=c17 -Wall -o FindPath FindPath.o Graph.o List.o

FindPath.o : FindPath.c Graph.h
	gcc -std=c17 -Wall -c FindPath.c

GraphTest : GraphTest.o Graph.o List.o
	gcc -std=c17 -Wall -o GraphTest GraphTest.o Graph.o List.o

GraphTest.o : GraphTest.c Graph.h
	gcc -std=c17 -Wall -c GraphTest.c

Graph.o : Graph.c Graph.h List.h
	gcc -std=c17 -Wall -c Graph.c

List.o : List.c List.h
	gcc -std=c17 -Wall -c List.c

clean :
	rm -f FindPath GraphTest FindPath.o GraphTest.o Graph.o List.o

checkTest :
	valgrind --leak-check=full GraphTest

checkFindPath :
	valgrind --leak-check=full FindPath testIn.txt testOut.txt
