#include "pane.h"
#include "tetris.h"
void InfoPane::draw() {
	    wattron(win,COLOR_PAIR(2) | A_BOLD); // color_pair and bold effect
	    box(win,0,0);
	    mvwprintw(win,1,1,"Your level : ");
	    mvwprintw(win,1,13," 1 ");
	   // else if(level2) mvwprintw(win,0,13," 2 ");
	   // else if(level3) mvwprintw(win,0,13," 3 ");

	    mvwprintw(win,2,1,"Full lines : ");
	    mvwprintw(win,2,13," 0 ");
	    mvwprintw(win,3,2,"SCORE");
	    mvwprintw(win,3,12,"  0  ");
	    wattroff(win,COLOR_PAIR(2) | A_BOLD);
	    wrefresh(win);
}

void InfoPane::drawInfo() {
	    wattron(win,COLOR_PAIR(2) | A_BOLD);
	    if(level1) mvwprintw(win,1,13," 1 ");
	    else if(level2) mvwprintw(win,1,13," 2 ");
	    else if(level3) mvwprintw(win,1,13," 3 ");
	    mvwprintw(win,2,13," %d ",fullLine);
	    mvwprintw(win,3,12,"  %d  ",score);
	    wattroff(win,COLOR_PAIR(2) | A_BOLD);
	    wrefresh(win);
}
