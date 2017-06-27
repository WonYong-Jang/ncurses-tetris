#ifndef TETRIS_H
#define TETRIS_H
#include "pane.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#define MAX_RANDOM 100
using namespace std;
class Tetris {
    Pane *infoPane, *helpPane, *nextPane, *boardPane, *statPane;
    int input;
    int type, rotation;
    static int curType,nextType;
    public:
	Tetris();
	~Tetris();
	void play(); // play tetris
	void setRandomType();
        void setBlock(int block[][MAX_ROTATION][BINDEX][BINDEX]); // All kinds of blocks
	void selectBlock(); // seletion of all blocks
	void updateScreen(); 
	int block[MAX_TYPE][MAX_ROTATION][BINDEX][BINDEX]; //All blocks[kind], [rotation], [horizontal blocks], [vertical blocks] 
	int selCurBlock[MAX_ROTATION][BINDEX][BINDEX]; // Selected current block
        int selNexBlock[MAX_ROTATION][BINDEX][BINDEX]; // Selected next block	
	int randomTypes[MAX_RANDOM];
};
#endif
