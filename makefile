randwrite: randwrite.o list.o
	g++ -o randwrite randwrite.o list.o	
randwrite.o: randwrite.cc
	g++ -c randwrite.cc.
list.o: list.cc list.h
	g++ -c list.cc