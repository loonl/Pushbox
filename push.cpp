#include <ncurses.h>

int map[3][100][100] = {                        {{1,1,1,1,0,0,0},
						 {1,3,2,1,1,0,0},
						 {1,3,2,3,1,0,0},
						 {1,3,2,4,1,0,0},
						 {1,1,4,4,1,1,1},
						 {0,1,4,4,4,4,1},
						 {0,1,4,6,3,4,1},
						 {0,1,4,5,4,4,1},
						 {0,1,1,1,1,1,1}},  // first map end


						{{1,1,1,1,1,1,1},
						 {1,5,4,4,4,4,1},
						 {1,4,2,2,2,4,1},
						 {1,4,3,3,3,3,1},
						 {1,4,4,4,4,4,1},
						 {1,4,4,4,4,2,1},
						 {1,4,4,4,4,4,1},
						 {1,1,1,1,1,1,1}}  // second map end

}; // map max size = 100 x 100, 3 maps / sero - garo
int curx = 0;
int cury = 0;
int my_location[2];
int test = 0;
// 0 = black, wall outside
// 1 = red wall 
// 2 = box (maximum box limit = 3)
// 3 = where box must be placed
// 4 = white movable space
// 5 = ME(playable character)
// 6 = box on 3
// 7 = ME on 3

void push(int current_map_idx);
void Map(int current_map_idx); // printing out real map

int main() {
	int ch;
	initscr();
	keypad(stdscr, TRUE);
	for (int i = 0; i < 2; i++) { // number of maps 
 // using while(answer == now box location) and implement this code there
		Map(i);
		while (true) {
			push(i);
			test++;
			if (test == 10) // if over 10 = move onto next map 
				break;
		}
		erase();
	}
	endwin();
	return 0;
}

void Map(int current_map_idx) {
	move(cury++, curx);
	start_color();
	for (int i = 0; i < 100; i++) { // don't need to be touched/sero
		for (int j = 0; j < 7; j++) { // must be touched! - always fit to garo size/garo
			int m = map[current_map_idx][i][j];
			switch (m) {
			case 0:
				printw(" ");
				break;
			case 1:
				init_pair(1, COLOR_RED, COLOR_RED);
				attron(COLOR_PAIR(1));
				printw(" ");
				attroff(COLOR_PAIR(1));
				break;
			case 2:
				init_pair(2, COLOR_YELLOW, COLOR_WHITE);
				attron(COLOR_PAIR(2));
				printw("X");
				attroff(COLOR_PAIR(2));
				break;
			case 3:
				init_pair(3, COLOR_WHITE, COLOR_GREEN);
				attron(COLOR_PAIR(3));
				printw("O");
				attroff(COLOR_PAIR(3));
				break;
			case 4:
				init_pair(4, COLOR_WHITE, COLOR_WHITE);
				attron(COLOR_PAIR(4));
				printw(" ");
				attroff(COLOR_PAIR(4));
				break;
			case 5:
				init_pair(5, COLOR_BLACK, COLOR_WHITE);
				attron(COLOR_PAIR(5));
				printw("!");
				my_location[0] = i;
				my_location[1] = j;
				attroff(COLOR_PAIR(5));
				break;
			case 6: // box on 3
				init_pair(6, COLOR_WHITE, COLOR_GREEN);
				attron(COLOR_PAIR(6));
				printw("X");
				attroff(COLOR_PAIR(6));
				break;
			case 7: // ME on 3
				init_pair(7, COLOR_BLACK, COLOR_GREEN);
				attron(COLOR_PAIR(7));
				printw("!");
				my_location[0] = i;
				my_location[1] = j;
				attroff(COLOR_PAIR(7));
				break;
			} // end switch case
			if (j == 6)
				move(cury++, 0);
		} // end for j
	} // end for i
	refresh();
	curs_set(0);
	cury = 0;
	curx = 0;
}

void push(int current_map_idx) {
	int ch = getch(); // get input
	int pos_current, pos_next, pos_nexnext;
	switch (ch) {
	case KEY_UP:
		pos_current = map[current_map_idx][my_location[0]][my_location[1]];
		pos_next = map[current_map_idx][my_location[0] - 1][my_location[1]];
		pos_nexnext = map[current_map_idx][my_location[0] - 2][my_location[1]];
		if (pos_next == 1)
			break;
		if (pos_next == 2) {
			if (pos_nexnext == 1)
				break;
			if (pos_nexnext == 2)
				break;
			if (pos_nexnext == 3) {
				map[current_map_idx][my_location[0] - 2][my_location[1]] = 6;
				map[current_map_idx][my_location[0] - 1][my_location[1]] = 5;
				if (pos_current == 7)
					map[current_map_idx][my_location[0]][my_location[1]] = 3;
				if (pos_current == 5)
					map[current_map_idx][my_location[0]][my_location[1]] = 4;
				break;
			}
			if (pos_nexnext == 4) {
				map[current_map_idx][my_location[0] - 2][my_location[1]] = 2;
				map[current_map_idx][my_location[0] - 1][my_location[1]] = 5;
				if (pos_current == 7)
					map[current_map_idx][my_location[0]][my_location[1]] = 3;
				if (pos_current == 5)
					map[current_map_idx][my_location[0]][my_location[1]] = 4;
				break;
			}
			if (pos_nexnext == 6)
				break;
		} // end if 2
		if (pos_next == 3) {
			map[current_map_idx][my_location[0] - 1][my_location[1]] = 7;
			if (pos_current == 5)
				map[current_map_idx][my_location[0]][my_location[1]] = 4;
			if (pos_current == 7)
				map[current_map_idx][my_location[0]][my_location[1]] = 3;
			break;
		} // end if 3
		if (pos_next == 4) {
			map[current_map_idx][my_location[0] - 1][my_location[1]] = 5;
			if (pos_current == 7)
				map[current_map_idx][my_location[0]][my_location[1]] = 3;
			if (pos_current == 5)
				map[current_map_idx][my_location[0]][my_location[1]] = 4;
			break;
		} // end if 4
		if (pos_next == 6) {
			if (pos_nexnext == 1)
				break;
			if (pos_nexnext == 2)
				break;
			if (pos_nexnext == 3) {
				map[current_map_idx][my_location[0] - 2][my_location[1]] = 6;
				map[current_map_idx][my_location[0] - 1][my_location[1]] = 7;
				if (pos_current == 5)
					map[current_map_idx][my_location[0]][my_location[1]] = 4;
				if (pos_current == 7)
					map[current_map_idx][my_location[0]][my_location[1]] = 3;
				break;
			}
			if (pos_nexnext == 4) {
				map[current_map_idx][my_location[0] - 2][my_location[1]] = 2;
				map[current_map_idx][my_location[0] - 1][my_location[1]] = 7;
				if (pos_current == 5)
					map[current_map_idx][my_location[0]][my_location[1]] = 4;
				if (pos_current == 7)
					map[current_map_idx][my_location[0]][my_location[1]] = 3;
				break;
			}
			if (pos_nexnext == 6)
				break;
		} // end if 6 
	 // END CASE KEY_UP

	case KEY_DOWN:
		pos_current = map[current_map_idx][my_location[0]][my_location[1]];
		pos_next = map[current_map_idx][my_location[0] + 1][my_location[1]];
		pos_nexnext = map[current_map_idx][my_location[0] + 2][my_location[1]];
		if (pos_next == 1)
			break;
		if (pos_next == 2) {
			if (pos_nexnext == 1)
				break;
			if (pos_nexnext == 2)
				break;
			if (pos_nexnext == 3) {
				map[current_map_idx][my_location[0] + 2][my_location[1]] = 6;
				map[current_map_idx][my_location[0] + 1][my_location[1]] = 5;
				if (pos_current == 7)
					map[current_map_idx][my_location[0]][my_location[1]] = 3;
				if (pos_current == 5)
					map[current_map_idx][my_location[0]][my_location[1]] = 4;
				break;
			}
			if (pos_nexnext == 4) {
				map[current_map_idx][my_location[0] + 2][my_location[1]] = 2;
				map[current_map_idx][my_location[0] + 1][my_location[1]] = 5;
				if (pos_current == 7)
					map[current_map_idx][my_location[0]][my_location[1]] = 3;
				if (pos_current == 5)
					map[current_map_idx][my_location[0]][my_location[1]] = 4;
				break;
			}
			if (pos_nexnext == 6)
				break;
		} // end if 2
		if (pos_next == 3) {
			map[current_map_idx][my_location[0] + 1][my_location[1]] = 7;
			if (pos_current == 5)
				map[current_map_idx][my_location[0]][my_location[1]] = 4;
			if (pos_current == 7)
				map[current_map_idx][my_location[0]][my_location[1]] = 3;
			break;
		} // end if 3
		if (pos_next == 4) {
			map[current_map_idx][my_location[0] + 1][my_location[1]] = 5;
			if (pos_current == 7)
				map[current_map_idx][my_location[0]][my_location[1]] = 3;
			if (pos_current == 5)
				map[current_map_idx][my_location[0]][my_location[1]] = 4;
			break;
		} // end if 4
		if (pos_next == 6) {
			if (pos_nexnext == 1)
				break;
			if (pos_nexnext == 2)
				break;
			if (pos_nexnext == 3) {
				map[current_map_idx][my_location[0] + 2][my_location[1]] = 6;
				map[current_map_idx][my_location[0] + 1][my_location[1]] = 7;
				if (pos_current == 5)
					map[current_map_idx][my_location[0]][my_location[1]] = 4;
				if (pos_current == 7)
					map[current_map_idx][my_location[0]][my_location[1]] = 3;
				break;
			}
			if (pos_nexnext == 4) {
				map[current_map_idx][my_location[0] + 2][my_location[1]] = 2;
				map[current_map_idx][my_location[0] + 1][my_location[1]] = 7;
				if (pos_current == 5)
					map[current_map_idx][my_location[0]][my_location[1]] = 4;
				if (pos_current == 7)
					map[current_map_idx][my_location[0]][my_location[1]] = 3;
				break;
			}
			if (pos_nexnext == 6)
				break;
		} // end if 6
		// END SWITCH KEY_DOWN

	case KEY_RIGHT:
		pos_current = map[current_map_idx][my_location[0]][my_location[1]];
		pos_next = map[current_map_idx][my_location[0]][my_location[1] + 1];
		pos_nexnext = map[current_map_idx][my_location[0]][my_location[1] + 2];
		if (pos_next == 1)
			break;
		if (pos_next == 2) {
			if (pos_nexnext == 1)
				break;
			if (pos_nexnext == 2)
				break;
			if (pos_nexnext == 3) {
				map[current_map_idx][my_location[0]][my_location[1] + 2] = 6;
				map[current_map_idx][my_location[0]][my_location[1] + 1] = 5;
				if (pos_current == 7)
					map[current_map_idx][my_location[0]][my_location[1]] = 3;
				if (pos_current == 5)
					map[current_map_idx][my_location[0]][my_location[1]] = 4;
				break;
			}
			if (pos_nexnext == 4) {
				map[current_map_idx][my_location[0]][my_location[1] + 2] = 2;
				map[current_map_idx][my_location[0]][my_location[1] + 1] = 5;
				if (pos_current == 7)
					map[current_map_idx][my_location[0]][my_location[1]] = 3;
				if (pos_current == 5)
					map[current_map_idx][my_location[0]][my_location[1]] = 4;
				break;
			}
			if (pos_nexnext == 6)
				break;
		} // end if 2
		if (pos_next == 3) {
			map[current_map_idx][my_location[0]][my_location[1] + 1] = 7;
			if (pos_current == 5)
				map[current_map_idx][my_location[0]][my_location[1]] = 4;
			if (pos_current == 7)
				map[current_map_idx][my_location[0]][my_location[1]] = 3;
			break;
		} // end if 3
		if (pos_next == 4) {
			map[current_map_idx][my_location[0]][my_location[1] + 1] = 5;
			if (pos_current == 7)
				map[current_map_idx][my_location[0]][my_location[1]] = 3;
			if (pos_current == 5)
				map[current_map_idx][my_location[0]][my_location[1]] = 4;
			break;
		} // end if 4
		if (pos_next == 6) {
			if (pos_nexnext == 1)
				break;
			if (pos_nexnext == 2)
				break;
			if (pos_nexnext == 3) {
				map[current_map_idx][my_location[0]][my_location[1] + 2] = 6;
				map[current_map_idx][my_location[0]][my_location[1] + 1] = 7;
				if (pos_current == 5)
					map[current_map_idx][my_location[0]][my_location[1]] = 4;
				if (pos_current == 7)
					map[current_map_idx][my_location[0]][my_location[1]] = 3;
				break;
			}
			if (pos_nexnext == 4) {
				map[current_map_idx][my_location[0]][my_location[1] + 2] = 2;
				map[current_map_idx][my_location[0]][my_location[1] + 1] = 7;
				if (pos_current == 5)
					map[current_map_idx][my_location[0]][my_location[1]] = 4;
				if (pos_current == 7)
					map[current_map_idx][my_location[0]][my_location[1]] = 3;
				break;
			}
			if (pos_nexnext == 6)
				break;
		} // end if 6
		// END SWITCH KEY_RIGHT

	case KEY_LEFT:
		pos_current = map[current_map_idx][my_location[0]][my_location[1]];
		pos_next = map[current_map_idx][my_location[0]][my_location[1] - 1];
		pos_nexnext = map[current_map_idx][my_location[0]][my_location[1] - 2];
		if (pos_next == 1)
			break;
		if (pos_next == 2) {
			if (pos_nexnext == 1)
				break;
			if (pos_nexnext == 2)
				break;
			if (pos_nexnext == 3) {
				map[current_map_idx][my_location[0]][my_location[1] - 2] = 6;
				map[current_map_idx][my_location[0]][my_location[1] - 1] = 5;
				if (pos_current == 7)
					map[current_map_idx][my_location[0]][my_location[1]] = 3;
				if (pos_current == 5)
					map[current_map_idx][my_location[0]][my_location[1]] = 4;
				break;
			}
			if (pos_nexnext == 4) {
				map[current_map_idx][my_location[0]][my_location[1] - 2] = 2;
				map[current_map_idx][my_location[0]][my_location[1] - 1] = 5;
				if (pos_current == 7)
					map[current_map_idx][my_location[0]][my_location[1]] = 3;
				if (pos_current == 5)
					map[current_map_idx][my_location[0]][my_location[1]] = 4;
				break;
			}
			if (pos_nexnext == 6)
				break;
		} // end if 2
		if (pos_next == 3) {
			map[current_map_idx][my_location[0]][my_location[1] - 1] = 7;
			if (pos_current == 5)
				map[current_map_idx][my_location[0]][my_location[1]] = 4;
			if (pos_current == 7)
				map[current_map_idx][my_location[0]][my_location[1]] = 3;
			break;
		} // end if 3
		if (pos_next == 4) {
			map[current_map_idx][my_location[0]][my_location[1] - 1] = 5;
			if (pos_current == 7)
				map[current_map_idx][my_location[0]][my_location[1]] = 3;
			if (pos_current == 5)
				map[current_map_idx][my_location[0]][my_location[1]] = 4;
			break;
		} // end if 4
		if (pos_next == 6) {
			if (pos_nexnext == 1)
				break;
			if (pos_nexnext == 2)
				break;
			if (pos_nexnext == 3) {
				map[current_map_idx][my_location[0]][my_location[1] - 2] = 6;
				map[current_map_idx][my_location[0]][my_location[1] - 1] = 7;
				if (pos_current == 5)
					map[current_map_idx][my_location[0]][my_location[1]] = 4;
				if (pos_current == 7)
					map[current_map_idx][my_location[0]][my_location[1]] = 3;
				break;
			}
			if (pos_nexnext == 4) {
				map[current_map_idx][my_location[0]][my_location[1] - 2] = 2;
				map[current_map_idx][my_location[0]][my_location[1] - 1] = 7;
				if (pos_current == 5)
					map[current_map_idx][my_location[0]][my_location[1]] = 4;
				if (pos_current == 7)
					map[current_map_idx][my_location[0]][my_location[1]] = 3;
				break;
			}
			if (pos_nexnext == 6)
				break;
		} // end if 6
		// END SWITCH KEY_LEFT

	} // end switch case
	erase();
	Map(current_map_idx);
}
