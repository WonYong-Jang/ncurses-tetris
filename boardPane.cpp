#include "pane.h"
#include "tetris.h"
void BoardPane::draw() {
	    wattron(win,COLOR_PAIR(5));
	    mvwvline(win,1,0,ACS_DIAMOND,height);
	    mvwvline(win,1,width-1,ACS_DIAMOND,height);
	    mvwhline(win,height-1,0,ACS_DIAMOND,width);
	    wattroff(win,COLOR_PAIR(5));

	    wattron(win,A_BOLD);
	    mvwvline(win,6,3,ACS_VLINE,height-15);
	    mvwvline(win,6,width-3,ACS_VLINE,height-15);
	    mvwhline(win,height-10,3,ACS_S1,width-5);
	    mvwhline(win,6,3,ACS_S9,width-5);
	    mvwprintw(win,8,6,"Press any key");
	    mvwprintw(win,9,8,"to play !");
	    wattroff(win,A_BOLD);
	
	    wrefresh(win);
	    for(int i =0;i<MAX_BOARD;i++)
	    {
		for(int j=0;j<MAX_BOARD;j++)
		{
		    board[i][j] = VOID;
		}
	    }
	    quitKey = 0;
	    firstScreen =1;
}
void BoardPane::connectPoint(InfoPane *info) {
	    this->info = info;
}
void BoardPane::clearOneLine(int line) {
	    for(int i=0; i<MAX_BOARD;i++)
		board[line][i] = VOID; // Clear a line in the board
	    
	    for(int i=line-1; i>=0; i--) // Move one line when one line is cleared
		for(int j=0; j<MAX_BOARD; j++)
		    board[i+1][j] = board[i][j];

	    for(int i=3;i<MAX_BOARD;i++)
		    mvwprintw(win,i,2,"                    "); // Clear a line in the BoardPane

	    for(int i =0; i<=line; i++) // Draw tetris block 
	    {
		for(int j=0; j<MAX_BOARD; j++)
		{
		    if(board[i][j] != VOID)
		    {
		        wattron(win,COLOR_PAIR(board[i][j]-3));
		        mvwhline(win,i,j,ACS_CKBOARD,2);
		        wattroff(win,COLOR_PAIR(2));
		    }
		}
	    }
}
Board BoardPane::getBlockType(int type) { 
	    Board result = VOID;
	    switch(type) // To save color by type
	    {
		case 0: result = S;
			break;
		case 1: result = I;
			break;
		case 2: result = L;
			break;
		case 3: result = L_MIR;
			break;
		case 4: result = N;
			break;
		case 5: result = N_MIR;
			break;
		case 6: result = T;
			break;
	    }
	    return result;
}
void BoardPane::isFullLine() {
	    int count,flag=0;
	    for(int i=0; i<MAX_BOARD; i++)
	    {
		count=0;
		for(int j=0; j<MAX_BOARD; j++)
		{
		    if( board[i][j] != VOID) count++; // Check if a line is full
		}
		if(count == 10)
		{
		    mvwprintw(win,i,2,"                    "); // Clear a line in the BoardPane
		    clearOneLine(i);
		    fullLine++;
		    score+=10;
		    info -> drawInfo();
		}
	    }
	    if(score == 500) bonusClear();
}
void BoardPane::drawBlock(int block[][BINDEX][BINDEX],int type,int rotation) {
	    int downPos=0, endX=0,leftX=5,rightX=0, num=0,flag, x, y, tempRotation=0;
	    xMove=width/2, yMove=0; // Starting point of block
	    
	    blockType[type]++; // To show block number of statPane
	    bRotation = rotation;
	    for(int p=0; p<MAX_BOARD; p++)
	    {
		if(checkGameOver() == GAMEOVER)
		{
		    endScreen();
		    break;
		}
		
		if(quitKey == PRESSED) break;
		flag=0; // Check if there is a block below
		x = 0;
		y = 0;
		input=getch();
		timeout(10); // Getch will only wait 0.01 second
		moveBlock(input);
		if(input == KEY_UP)
		{
		    leftX=5;
		    rightX=0;
		    tempRotation=bRotation;
		    tempRotation++;
		    if(tempRotation >3) tempRotation -=4;
		    for(int i =0; i<BINDEX; i++) 
		    {
			for(int j=0; j<BINDEX; j++)
			{
			    if((block[tempRotation][i][j] != VOID) && (block[tempRotation][i][j] !=FULL))
			    {
			    	leftX = (leftX > j ? j : leftX );   // The leftmost of the blocks
				rightX = (rightX < j ? j : rightX); //the rightmost of the blocks
			    }
			}
		    }
		    xLeftPos = leftX*2+xMove;
		    xRightPos =rightX*2+xMove;
   
		    if( xRightPos <= 20 && xLeftPos >=2)
		    {
			bRotation += 1;
			if(bRotation > 3) bRotation -= 4;
		    }
		}
		if(firstScreen==1) {
		    delScreen();
		    firstScreen -=1;
		}
		leftX=5;
		rightX=0;
		for(int i =0; i<BINDEX; i++) // Draw tetris block 
		{
		    for(int j=0; j<BINDEX; j++)
		    {
			if((block[bRotation][i][j] != VOID) && (block[bRotation][i][j] !=FULL))
			{
			    leftX = (leftX > j ? j : leftX );   // The leftmost of the blocks
			    rightX = (rightX < j ? j : rightX); //the rightmost of the blocks
			    wattron(win,COLOR_PAIR(type+2));
			    mvwhline(win,i+downPos,j*2+xMove,ACS_CKBOARD,2);
			    wattroff(win,COLOR_PAIR(type+2));
			}
			if(block[bRotation][i][j] == BOUNDARY) // Remember end coordinate
			    endX =i;
			if(block[bRotation][i][j] == FULL)     // Check if there is a block below
			{
			    x = j*2+xMove;
			    y = i+downPos;
			    for(int i=0; i<MAX_BOARD; i++)
			    {
				for(int j=0; j<MAX_BOARD; j++)
				{
				    if(board[i][j] !=VOID)
				    {
					if( (j == x) && (i ==y) ) flag=1;
				    }
				}
			    }
			}
			    
		    }
		}
		xLeftPos = leftX*2+xMove;
		xRightPos =rightX*2+xMove;
	    	//mvwprintw(win,num++,2,"(%d,%d), (%d)",xLeftPos,xRightPos,bRotation);
		wrefresh(win);
		if(spaceKey == NOT_PRESSED) 
		{
		    if(level1 == PRESSED) usleep(310000);
		    else if(level2 == PRESSED) usleep(210000);
		    else if(level3 == PRESSED) usleep(110000);
		}
		if( (endX+downPos == height-2)|| flag==1) // Stop if there is an obstacle below
		{
		    for(int i=0; i<BINDEX; i++)
		    {
			for(int j=0;j<BINDEX; j++)
			{
			    if(block[bRotation][i][j] != VOID && block[bRotation][i][j] != FULL)
			    {
				yPos = i+downPos;
				xPos = j*2+xMove;
				board[yPos][xPos] = getBlockType(type);
			    }
			}
		    }
		    flushinp(); // routine throws away any typeahead that has been typed by the user and has not yet been read by the program.
		    continue;
		}
		for(int i=0; i<BINDEX; i++) // Clear existing location block
		{
		    for(int j=0; j<BINDEX; j++)
		    {
			if(block[bRotation][i][j] !=VOID && block[bRotation][i][j] != FULL)
			     mvwprintw(win,i+downPos,j*2+xMove,"  ");
		    }
		}
		wrefresh(win);
		if(spaceKey ==NOT_PRESSED) 
		{
		   if(level1 == PRESSED) usleep(310000);
		   else if(level2 == PRESSED) usleep(210000);
		   else if(level3 == PRESSED) usleep(110000);
		}
		downPos++; // Move down block automatically
	    }
	    isFullLine();
	spaceKey=NOT_PRESSED;
}
Game BoardPane::checkGameOver() {
    for(int i=0; i<MAX_BOARD;i++)
    {
	if(board[2][i])
	{ 
	    gameOver = GAMEOVER;
	}
    }
  return gameOver;  
}
void BoardPane::moveBlock(int input)
{
    if(xRightPos+2 < width-2 && input == KEY_RIGHT) // Right
    {
	xMove+=2;
    }
    else if(xLeftPos-2 > 1 && input == KEY_LEFT) // Left
    {
        xMove-=2;
    }
    if(input == 32) // In case of input space key, Drop block
    {
	spaceKey = PRESSED;
    }
    if(input == 113) // Quit
    {
	quitKey = PRESSED;
    }
    if(input == 50) // Level1
    {
	level1 = PRESSED;
	level2 = NOT_PRESSED;
	level3 = NOT_PRESSED;
	info -> drawInfo(); // Update immediately
    }
    else if(input ==51) // Level2
    {
	level1 = NOT_PRESSED;
	level2 = PRESSED;
	level3 = NOT_PRESSED;
	info -> drawInfo();
    }
    else if(input ==52) // Level3
    {
	level1 = NOT_PRESSED;
	level2 = NOT_PRESSED;
	level3 = PRESSED;
	info -> drawInfo();
    }
}
void BoardPane::delScreen() {
    for(int i=0; i<12;i++){
	mvwprintw(win,2+i,2,"                     ");
    }
}
void BoardPane::endScreen() {
	delScreen();
	wattron(win,A_BOLD);
	mvwvline(win,6,3,ACS_VLINE,height-15);
	mvwvline(win,6,width-3,ACS_VLINE,height-15);
	mvwhline(win,height-10,3,ACS_S1,width-5);
	mvwhline(win,6,3,ACS_S9,width-5);
	mvwprintw(win,9,6,"GAME OVER !!!");
	wattroff(win,A_BOLD);
	wrefresh(win);
	timeout(-1);
	getch();

}
void BoardPane::bonusClear() {	
	mvwprintw(win,20,2,"                    "); // Clear a line in the BoardPane
	clearOneLine(20);
	score -= 500;
}









