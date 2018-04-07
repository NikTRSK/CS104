all: hashtest splaytest

hashtest: hash_sol.o hashtest
	g++ -g -std=c++11 -Wall hash_sol.o hashtest.cpp -o hashtest

splaytest: splaytest.cpp 
	g++ -g -std=c++11 -Wall splaytest.cpp  -o splaytest

clean:
	rm splaytest
	rm hashtest