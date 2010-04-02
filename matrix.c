// Falling "matrix" code.
// A simple implementation of ncurses.
// 
// mindfuzz.net
//
// Compile like so:
// gcc matrix.c -lncurses -o matrix
//
// Then execute
// ./matrix (blue|red|green|grey)
//
// To exit ^C

#include <sys/ioctl.h>
#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>

#define MAX_CHARS 50

typedef struct coords {
	unsigned short int x;
	unsigned short int y;
	unsigned short int len;
	unsigned short int colour;
} point ;

bool mv(int x,int y);

int main(int argc, char *argv[])
{

	unsigned short int i, x, y, tmp, swidth, sheight, max_chars;
	bool red = false, green = false, blue = false, grey = false;

	srand(time(NULL));

	if ( argc > 1 ) {
		if (strcmp(argv[1], "red") == 0) 	red = true;
		if (strcmp(argv[1], "blue") == 0 ) 	blue = true;
		if (strcmp(argv[1], "green") == 0 )	green = true;
		if (strcmp(argv[1], "grey") == 0 )	grey = true;
	} else {
		green = true;
	}

	initscr();
	getmaxyx(stdscr,sheight,swidth);
	sheight--;
	swidth--;

	point pts[MAX_CHARS];
	for(i=0;i<MAX_CHARS; i++) {
		pts[i].x=rand() % sheight - (sheight/2);
		pts[i].y=rand() % swidth;
		pts[i].len=rand() % 13 + 1;
		pts[i].colour = rand() % 6 + 1;
	};

	start_color();
	
	for(tmp = 1; tmp < 8; tmp++) {
		init_pair(tmp, tmp, 0);
		if (red) 	init_color(tmp, 100+(tmp*100), 0, 0);
		if (green) 	init_color(tmp, 0, 100+(tmp*100), 0);
		if (blue) 	init_color(tmp, 0, 0, 100+(tmp*100));
		if (grey) 	init_color(tmp, 100+(tmp*100), 100+(tmp*100), 100+(tmp*100));
	}

	init_color(7, 1000,1000,1000);

	while(true)
	{
		for (i=0;i<MAX_CHARS; i++) {	
		
			x = pts[i].x;
			y = pts[i].y;

			attron(COLOR_PAIR(pts[i].colour));
		
			if (mv(pts[i].x,pts[i].y))
				printw("%c", rand() % 93 + 33 );
			
			if (pts[i].x < sheight) { 
				if (mv(pts[i].x+1,pts[i].y)) {
					attron(COLOR_PAIR(7));
					printw("%c", rand() % 93 + 33 );
				}
			}

			pts[i].x = pts[i].x + 1;

			if (pts[i].x > sheight) {
				pts[i].x = rand() % 20;
				pts[i].y = rand() % swidth;
			}

		}

		refresh();		
		usleep(100000/2);

	}

	getch();
	endwin();	
	return 0;

}

bool mv(int x, int y)
{
	if (x < 0) return false;
	if (y < 0) return false;

	move(x,y);

	return true;
}
