.PHONY: clean
all: test
test: main.o play.o game.o shapes.o
	g++ main.o play.o game.o shapes.o -o test
main.o: main.cpp play.h play.o
	g++ main.cpp -c -o main.o
play.o: play.cpp play.h game.o game.h shapes.o shapes.h
	g++ play.cpp -c -o play.o
game.o: game.cpp game.h shapes.o shapes.h
	g++ game.cpp -c -o game.o
shapes.o: shapes.cpp shapes.h
	g++ shapes.cpp -c -o shapes.o
clean:
	rm -rf main.o play.o game.o shapes.o ai.o
