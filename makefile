
all: clean out 

out: main.o edge.o path.o monitor.o
	g++ main.o edge.o path.o monitor.o -pthread -o out.out

main.o: main.cpp
	g++ -c main.cpp -o main.o 

path.o: path.cpp
	g++ -c path.cpp -o path.o 

main.o: edge.cpp
	g++ -c edge.cpp -o edge.o 

monitor.o: monitor.cpp
	g++ -c monitor.cpp -o monitor.o

clean: 
	rm -rf *.o
