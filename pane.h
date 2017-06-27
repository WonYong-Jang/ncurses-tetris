#ifndef PANE_H
#define PANE_H
#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
using namespace std;
#define BINDEX 5 // Block index 5 x 5
#define MAX_BOARD 21 // The array index in which to store the position of the block.
#define MAX_TYPE 7 // Type of blocks
#define MAX_ROTATION 4 // four rotation
typedef enum {VOID,BLOCK,AXIS,BOUNDARY,FULL,S,I,L,L_MIR,N,N_MIR,T} Board;
typedef enum {NOT_PRESSED,PRESSED} InputValue;
typedef enum {GAME,GAMEOVER} Game;
class Pane {
    protected:
	int height,width;
	int pointX, pointY;
	WINDOW *win;
    public:
	Pane(int h,int w,int y,int x):height(h),width(w),pointY(y),pointX(x) {
	    win=newwin(h,w,y,x);
	}
	virtual ~Pane() {
	    delwin(win);
	}
	virtual void draw(){
	    box(win,0,0);
	    wrefresh(win);
	}
	Board board[MAX_BOARD][MAX_BOARD]; // Check if there is blocks
	static int blockType[MAX_TYPE]; // 7 block types	
	static int level1, level2, level3, fullLine, score;
};
class InfoPane : public Pane {
    public:
	InfoPane(int h,int w,int y,int x) : Pane(h,w,y,x) {}
	void draw();
	void drawInfo();
};
class HelpPane : public Pane {
    public:
       HelpPane(int h,int w,int y,int x):Pane(h,w,y,x) {}
       void draw();
};
class NextPane : public Pane {
    public:
	NextPane(int h,int w,int y,int x):Pane(h,w,y,x) {}
	void draw();
	void nextBlock(int block[][BINDEX][BINDEX], int type,int rotation);
};

class BoardPane : public Pane {
    public:
	BoardPane(int h,int w,int y,int x):Pane(h,w,y,x) {}
	InfoPane *info;
	void draw();
	void connectPoint(InfoPane *info); // To update the screen immediately while drawing a block
	void drawBlock(int block[][BINDEX][BINDEX],int type,int rotation);
	void moveBlock(int input);
	void isFullLine(); // Check if a line is full
	void clearOneLine(int line); // Clear a line at a time
	Game checkGameOver();
	Board getBlockType(int type); // To store by type of block
	void delScreen(); // Clear Initial screen
	int quitKey;
	Game gameOver;
	void bonusClear(); // Run when the score exceeds 500 points
	void endScreen(); // Game end screen
    private:
	int input,firstScreen;
	int xMove,yMove,xRightPos,xLeftPos,yPos,xPos,chkRotation;
	int spaceKey,bRotation;
};
class StatPane :public Pane {
    public:
	StatPane(int h,int w,int y,int x):Pane(h,w,y,x) {}
	void draw();
	void selectedBlocks(); // Number of selected blocks
};
#endif


