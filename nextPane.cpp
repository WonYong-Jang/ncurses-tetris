#include "pane.h"
#include "tetris.h"
void NextPane::draw() {
	    wattron(win,COLOR_PAIR(4) | A_BOLD);
	 //   for(int i=0; i<height;i++)
//		mvwhline(win,i,0,ACS_CKBOARD,width);
	    box(win,0,0);
	    mvwprintw(win,2,3,"Next:");
	    wattroff(win,COLOR_PAIR(4) | A_BOLD);
	    wrefresh(win);
}
void NextPane::nextBlock(int block[][BINDEX][BINDEX], int type, int rotation)
{
    for(int i=0; i<BINDEX; i++)
    {
	for(int j=0; j<BINDEX; j++)
	{
		mvwprintw(win,i,j*2+10,"   ");
	}
    }
    wrefresh(win);
    for(int i =0; i<BINDEX ;i++)
    {
	for(int j=0; j<BINDEX ;j++)
	{
	    if(block[rotation][i][j] !=VOID && block[rotation][i][j] != FULL)
	    {
		wattron(win,COLOR_PAIR(type+2));
		mvwhline(win,i,j*2+10,ACS_CKBOARD,2);
		wattroff(win,COLOR_PAIR(type+2));
	    }
	}
    }
    wrefresh(win);
}
