programa: main.o funkcijos.o
	g++ main.o funkcijos.o -o programa

main.o: main.cpp antrastes.h
	g++ -c main.cpp

funkcijos.o: funkcijos.cpp antrastes.h
	g++ -c funkcijos.cpp

clean:
	rm -f *.o programa