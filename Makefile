OBJS	= main.o Input.o LevelBuilder.o Image.o
SOURCE	= main.cpp Input.cpp LevelBuilder.cpp Image.cpp
HEADER	= Input.h LevelBuilder.h Image.h
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

LevelBuilder.o: LevelBuilder.cpp
	$(CC) $(FLAGS) LevelBuilder.cpp -std=c++14

Image.o: Image.cpp
	$(CC) $(FLAGS) Image.cpp -std=c++14

clean:
	rm -f $(OBJS) $(OUT)
