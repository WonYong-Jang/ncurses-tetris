#include "pane.h"
#include "tetris.h"
void StatPane::draw() {
	    int sum =0;
	    for(int i=0; i<7; i++)
	    {
		sum+= blockType[i];
	    }
	    wattron(win,COLOR_PAIR(3) | A_BOLD);
	    mvwhline(win,height-4,0,ACS_S9,width);
	    mvwprintw(win,height-3,3,"Sum : ");
	    mvwprintw(win,height-3,18,"%d",sum);
	    mvwprintw(win,0,3,"STATISTICS");
	    wattroff(win,COLOR_PAIR(3) | A_BOLD);

	    mvwhline(win,height-4,0,ACS_S9,width);
	    wattron(win,COLOR_PAIR(4));
	    mvwhline(win,2,0,ACS_CKBOARD,6);
	    mvwhline(win,2,14,ACS_S7,2);
	    mvwprintw(win,2,18,"%d",blockType[2]);
	    mvwhline(win,3,0,ACS_CKBOARD,2);
	    wattroff(win,COLOR_PAIR(4));

	    wattron(win,COLOR_PAIR(3));
	    mvwhline(win,4,4,ACS_CKBOARD,8);
	    mvwhline(win,4,14,ACS_S7,2);
	    mvwprintw(win,4,18,"%d",blockType[1]);
	    wattroff(win,COLOR_PAIR(3));

	    wattron(win,COLOR_PAIR(8));
	    mvwhline(win,6,14,ACS_S7,2);
	    mvwprintw(win,6,18,"%d",blockType[6]);
	    mvwhline(win,6,0,ACS_CKBOARD,6);
	    mvwhline(win,7,2,ACS_CKBOARD,2);
	    wattroff(win,COLOR_PAIR(8));

	    wattron(win,COLOR_PAIR(7));
	    mvwhline(win,8,14,ACS_S7,2);
	    mvwprintw(win,8,18,"%d",blockType[5]);
	    mvwhline(win,8,8,ACS_CKBOARD,4);
	    mvwhline(win,9,6,ACS_CKBOARD,4);
	    wattroff(win,COLOR_PAIR(7));

	    wattron(win,COLOR_PAIR(6));
	    mvwhline(win,10,14,ACS_S7,2);
	    mvwprintw(win,10,18,"%d",blockType[4]);
	    mvwhline(win,10,0,ACS_CKBOARD,4);
	    mvwhline(win,11,2,ACS_CKBOARD,4);
	    wattroff(win,COLOR_PAIR(6));

	    wattron(win,COLOR_PAIR(2));
	    mvwhline(win,12,14,ACS_S7,2);
	    mvwprintw(win,12,18,"%d",blockType[0]);
	    mvwhline(win,12,8,ACS_CKBOARD,4);
	    mvwhline(win,13,8,ACS_CKBOARD,4);
	    wattroff(win,COLOR_PAIR(2));
	    
	    wattron(win,COLOR_PAIR(5));
	    mvwhline(win,14,0,ACS_CKBOARD,6);
	    mvwhline(win,14,14,ACS_S7,2);
	    mvwprintw(win,14,18,"%d",blockType[3]);
	    mvwhline(win,15,4,ACS_CKBOARD,2);
	    wattroff(win,COLOR_PAIR(5));

	    wrefresh(win);
}
