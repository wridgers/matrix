Project( matrix )

CMake_minimum_required(VERSION 2.6)

set (
	SOURCES
	./matrix.c
)

link_libraries( -lncurses )

add_executable (
	./matrix
	${SOURCES}
)
