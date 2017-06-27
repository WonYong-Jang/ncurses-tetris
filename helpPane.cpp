#include "pane.h"
#include "tetris.h"
void HelpPane::draw() {
	   wattron(win,COLOR_PAIR(3) | A_BOLD);
	  // for(int i=0;i<height;i++)
	   //    mvwhline(win,i,0,ACS_CKBOARD,width);
	   box(win,0,0);
	   mvwprintw(win,1,5,"H E L P");
	   mvwprintw(win,3,1,"<:Left");
	   mvwprintw(win,4,1,">:Right");
	   mvwprintw(win,5,1,"^:Rotate");
	   mvwprintw(win,6,1,"2:Level 1");
	   mvwprintw(win,7,1,"3:Level 2");
	   mvwprintw(win,8,1,"4:Level 3");
	   mvwprintw(win,9,2,"SPACE:Drop");
	   mvwprintw(win,10,1,"q:Quit");
	   wattroff(win,COLOR_PAIR(3) | A_BOLD);
	   wrefresh(win);
}
