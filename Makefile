CC = gcc
NAME = get_next_line
CFLAGS = -Wall -Werror -Wextra
VALGRIND = valgrind -q --leak-check=full --track-origins=yes --verbose

${NAME}:
	${CC} ${CFLAGS} -c -D BUFFER_SIZE=10 get_next_line.c get_next_line_utils.c

all: ${NAME}

clean:
	rm -f *.o
fclean: clean
	rm -f ${NAME}
re: fclean all
