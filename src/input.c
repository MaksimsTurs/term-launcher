#include "input.h"

char launcher_read_char()
{
	char buff[LAUNCHER_READ_BUFF_SIZE] = {0};
	t_termios old_term = {0};
	t_termios new_term = {0};

	tcgetattr(STDIN_FILENO, &old_term);
	new_term = old_term;
	new_term.c_lflag &= ~(ICANON | ECHO);

	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
	read(STDIN_FILENO, buff, LAUNCHER_READ_BUFF_SIZE);
	fflush(stdout);
	tcsetattr(STDIN_FILENO, TCSANOW, &old_term);

	// Chek is Arrow buttons are pressed.
	if((buff[0] == 27 || buff[0] == 7) && buff[1] == 91)
	{
		return buff[2];
	}

	return buff[0];
}

void launcher_input_buffer_push(t_input_buffer* buffer, char ch)
{
	if(buffer->size + 1 < LAUNCHER_INPUT_BUFFER_SIZE)
	{
		buffer->value[buffer->size] = ch;
		buffer->size++;
	}
}

void launcher_input_buffer_pop(t_input_buffer* buffer)
{
	if(buffer->size > 0)
	{
		buffer->value[buffer->size - 1] = 0;
		buffer->size--;
	}
}
