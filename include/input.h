#ifndef H_LAUNCHER_INPUT
#define H_LAUNCHER_INPUT

#include <termios.h>
#include <stdio.h>
#include <unistd.h>

#define LAUNCHER_READ_BUFF_SIZE 	3

#define LAUNCHER_INPUT_BUFFER_SIZE 1024

typedef struct termios t_termios;

typedef struct s_input_buffer {
	char 	value[LAUNCHER_INPUT_BUFFER_SIZE];
	int		size;
} t_input_buffer;

void launcher_input_buffer_push(t_input_buffer* buffer, char ch);
void launcher_input_buffer_pop(t_input_buffer* buffer);

char launcher_read_char();

#endif
