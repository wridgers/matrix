all:
		gcc matrix.c -l ncurses -o matrix

clean:
		rm matrix
