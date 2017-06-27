#include "tetris.h"
#include "pane.h"
int Tetris::curType = 0;
int Tetris::nextType = 1;
Tetris::Tetris(){
	    initscr(); // Start Curses mode 
	    start_color(); // Declaration color attribute
	  //  cbreak();

	    curs_set(0);
	    keypad(stdscr,TRUE); // Input key
	    noecho();
	    
	    type=rotation=0;

	    srand((unsigned)time(NULL)); // To use random blocks

	    init_pair(2,COLOR_GREEN, COLOR_BLACK); // Set color attribute
	    init_pair(3,COLOR_WHITE,COLOR_BLACK);
	    init_pair(4,COLOR_CYAN,COLOR_BLACK);
	    init_pair(5,COLOR_BLUE,COLOR_BLACK);
	    init_pair(6,COLOR_RED,COLOR_BLACK);
	    init_pair(7,COLOR_MAGENTA,COLOR_BLACK);
	    init_pair(8,COLOR_YELLOW,COLOR_BLACK);

	    attron(COLOR_PAIR(6) | A_BOLD); // Apply to color attribute
	    mvprintw(22,36,"Play TETRIS !");
	    attroff(COLOR_PAIR(6) | A_BOLD);

	    refresh();

	    infoPane=new InfoPane(5,25,1,1);
	    helpPane=new HelpPane(12,25,6,1);
	    nextPane=new NextPane(5,25,18,1);
	    boardPane=new BoardPane(22,24,0,30);
	    statPane=new StatPane(20,20,3,60);
	    ((BoardPane*)boardPane)->connectPoint((InfoPane*)infoPane); // To update infoPane immediately
}
Tetris::~Tetris(){
	    delete infoPane;
	    delete helpPane;
	    delete nextPane;
	    delete boardPane;
	    delete statPane;
	    endwin(); // End Curses mode
}
void Tetris::play() {
	    int i=0;
	    updateScreen();

	    for(int i=0; i<MAX_RANDOM; i++)
		randomTypes[i] = 0;
	    randomTypes[MAX_BOARD] = rand() % 7;
	    ((BoardPane*)boardPane)->gameOver = GAME;
	    while(1)
	    {
		if( ((BoardPane*)boardPane)->gameOver == GAMEOVER) break;
		if( ((BoardPane*)boardPane)->quitKey == PRESSED) break;
		if(i % MAX_RANDOM ==0)
		{ 
		    setRandomType(); // Run once in 100 times
		    curType =0;
		    nextType =1;
		}
		statPane->draw();
		selectBlock();
		i++;
	    }
}
void Tetris::updateScreen(){
	    infoPane->draw();
	    helpPane->draw();
	    nextPane->draw();
	    boardPane->draw();
	    statPane->draw();
}
void Tetris::setRandomType() {
    int tempType =0;

    if(curType == 0) tempType = randomTypes[MAX_BOARD];
    for(int i=0; i<MAX_RANDOM; i++)
	randomTypes[i] = 0;

    for(int i=1; i<MAX_RANDOM ;i++)
    {
	randomTypes[i] = rand() % 7;
    }		
     randomTypes[0] = tempType;
}
void Tetris::selectBlock() { 
	//type = rand() % 7 ;             // 7 random types
	rotation = rand() % 4 ;         // 4 random rotations
	for(int k=0; k<MAX_ROTATION; k++)
	{
	    for(int i=0; i< BINDEX; i++)
	    {
		for(int j=0;j<BINDEX;j++)
		{
		    selCurBlock[k][i][j] =0;
		    selNexBlock[k][i][j] =0;
		}
	    }
	}
	curType++;
	nextType++;
	for(int k=0; k<MAX_ROTATION ;k++) // Current block
	{
	    for(int i =0 ; i< BINDEX; i++)
	    {
		for(int j=0; j<BINDEX; j++)
		{	
		   selCurBlock[k][i][j] = block[randomTypes[curType]][k][i][j];
		}
	    }
	}
	for(int k=0; k<MAX_ROTATION ;k++) // next block
	{
	    for(int i =0 ; i< BINDEX; i++)
	    {
		for(int j=0; j<BINDEX; j++)
		{	
		   selNexBlock[k][i][j] = block[randomTypes[nextType]][k][i][j];
		}
	    }
	}
	 ((NextPane*)nextPane)->nextBlock(selNexBlock,randomTypes[nextType],rotation);
	((BoardPane*)boardPane)->drawBlock(selCurBlock,randomTypes[curType],rotation);
}
void Tetris::setBlock(int block[][MAX_ROTATION][BINDEX][BINDEX]) { // Initialize
	int i,j,k,l;
    for(int i =0; i< MAX_TYPE;i++)
    {
	for(int j=0; j<MAX_ROTATION; j++)
	{
	    for(int k=0; k<BINDEX; k++)
	    {
		for(int l=0; l<BINDEX; l++)
		{
		    this->block[i][j][k][l] = block[i][j][k][l];
		}
	    }
	}
    }
}
