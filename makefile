all: earnings

earnings: earnings.o bst.o hashtable.o maxheap.o readEarning.o readODAfile.o prime.o bst.h hashtable.h maxheap.h readEarning.h readODAfile.h prime.h defns.h
	g++ -g earnings.o bst.o hashtable.o maxheap.o readEarning.o readODAfile.o prime.o -o earnings

earnings.o: earnings.cpp bst.h hashtable.h maxheap.h readEarning.h readODAfile.h prime.h defns.h
	g++ -g earnings.cpp -c -o earnings.o

bst.o: bst.cpp defns.h hashtable.h
	g++ -g bst.cpp -c -o bst.o

hashtable.o: hashtable.cpp defns.h hashtable.h
	g++ -g hashtable.cpp -c -o hashtable.o

maxheap.o: maxheap.cpp defns.h maxheap.h
	g++ -g maxheap.cpp -c -o maxheap.o

prime.o: prime.cpp prime.h
	g++ -g prime.cpp -c -o prime.o

readEarning.o: readEarning.cpp defns.h readEarning.h
	g++ -g readEarning.cpp -c -o readEarning.o

readODAfile.o: readODAfile.cpp defns.h readODAfile.h
	g++ -g readODAfile.cpp -c -o readODAfile.o

clean:
	rm *.o earnings -rf
