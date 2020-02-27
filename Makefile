OBJS	= main.o Input.o
SOURCE	= main.cpp Input.cpp
HEADER	= Input.h
OUT	= get-through
CC	 = g++
FLAGS	 = -g -c -Wall 
LFLAGS	 = -lm -lGL -lGLU -lglut

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++14

Input.o: Input.cpp
	$(CC) $(FLAGS) Input.cpp -std=c++14


clean:
	rm -f $(OBJS) $(OUT)
