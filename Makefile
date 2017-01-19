CC=g++
CFLAGS = -c -Wall
LIB = -lglut -lGL -lGLU

run: main.o visuals.o renders.o keyboard.o
	$(CC) main.o visuals.o renders.o keyboard.o $(LIB) -o run

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

visuals.o: visuals.cpp
	$(CC) $(CFLAGS) visuals.cpp

renders.o: renders.cpp
	$(CC) $(CFLAGS) renders.cpp

keyboard.o: keyboard.cpp
	$(CC) $(CFLAGS) keyboard.cpp

clean:
	rm -rf *o run
