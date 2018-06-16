all: exceptions.o user.o mysystem.o
	g++ main.cpp exceptions.o user.o mysystem.o

exceptions.o: exceptions.cpp
	g++ -c exceptions.cpp

user.o: user.cpp
	g++ -c user.cpp

mysystem.o: mysystem.cpp
	g++ -c mysystem.cpp
