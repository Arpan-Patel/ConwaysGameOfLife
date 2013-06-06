compile:
	g++ -L /usr/lib/ -I /home/arpan/c++/conwaysgameoflife/allegro-inc/include/allegro5/ game.cpp -o game `pkg-config --libs allegro allegro_primitives-5.0`
run:
	./game
clean:
	rm game

all: compile run
