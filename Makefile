tetris: main.o boardPane.o infoPane.o helpPane.o nextPane.o statPane.o tetris.o
	g++ -o tetris main.o boardPane.o infoPane.o helpPane.o nextPane.o statPane.o tetris.o -lncurses

main.o: tetris.h main.cpp
	g++ -c main.cpp -lncurses

tetris.o: tetris.h pane.h tetris.cpp
	g++ -c tetris.cpp -lncurses

boardPane.o: tetris.h pane.h boardPane.cpp
	g++ -c boardPane.cpp -lncurses

infoPane.o: tetris.h pane.h infoPane.cpp
	g++ -c infoPane.cpp -lncurses

helpPane.o: tetris.h pane.h helpPane.cpp
	g++ -c helpPane.cpp -lncurses

nextPane.o: tetris.h pane.h nextPane.cpp
	g++ -c nextPane.cpp -lncurses

statPane.o: tetris.h pane.h statPane.cpp
	g++ -c statPane.cpp -lncurses
