#include <ncurses.h>

int map[9][7] = {{1,1,1,1,4,4,4},{1,3,0,1,1,4,4},{1,3,0,0,1,4,4},{1,3,0,2,1,4,4},{1,1,2,0,1,1,1},{4,1,0,2,0,0,1},{4,1,0,0,0,0,1},{4,1,0,5,1,1,1},{4,1,1,1,1,4,4}};
int curx = 0;
int cury = 0;
// 0 = white movable space
// 1 = red wall 
// 2 = box
// 3 = where box must be placed
// 4 = black, wall outside 
// 5 = ME(playable character)
void Map() {
    move(cury++,curx);
 start_color();
 for(int i = 0; i <9; i++) {
    for(int j = 0; j <7; j++) {
   int m = map[i][j];
   switch(m) {
    case 0: 
            init_pair(1, COLOR_WHITE, COLOR_WHITE);
            attron(COLOR_PAIR(1));
	    printw(" ");
	    attroff(COLOR_PAIR(1));
	    break;
    case 1: 
            init_pair(2, COLOR_RED, COLOR_RED);
            attron(COLOR_PAIR(2));
	    printw(" ");
	    attroff(COLOR_PAIR(2));
	    break;
    case 2: 
            init_pair(3, COLOR_YELLOW, COLOR_WHITE);
            attron(COLOR_PAIR(3));
	    printw("X");
	    attroff(COLOR_PAIR(3));
	    break;
    case 3: 
            init_pair(4, COLOR_WHITE, COLOR_GREEN);
            attron(COLOR_PAIR(4));
	    printw("O");
	    attroff(COLOR_PAIR(4));
	    break;
    case 4: 
            printw(" ");
            break;
    case 5: 
            init_pair(5, COLOR_BLACK, COLOR_CYAN);
            attron(COLOR_PAIR(5));
            printw("!");
            break;
    }
	if(j == 6) 
            move(cury++,0); 
    }
}
 refresh();
 curs_set(0);
}

int main()
{
 initscr();
 Map();
 getch();
 endwin();
 return 0;
 }

