#include "main.h"
/**
 * pipe_getter - to get command for nonintractive mode
 * Description: for alx project simple shell
 * Return: 0 on success
 */

char **pipe_getter()
{
	int counter, flag = 0;
	size_t chara = 0;
	ssize_t bytes;
	char buffer[2048], *data = NULL, **commands = NULL;

	bytes = read(STDIN_FILENO, buffer, 2048);
	while (bytes > 0)
	{
		chara += bytes;
		bytes = read(STDIN_FILENO, buffer, 2048);
	}
	if (bytes == -1)
	{
		perror("read");
		exit(-1);
	}
	if (chara > 2048)
		buffer[2047] = '\0';
	else
		buffer[chara - 1] = '\0';
	for (counter = 0; buffer[counter]; counter++)
	{
		if (buffer[counter] != ' ' && buffer[counter] != '\n'
		&& buffer[counter] != '\t' && buffer[counter] != '\r'
		&& buffer[counter] != '\a')
		flag = 1;
	}
	if (flag == 0)
	return (NULL);
	chara = _strlen(buffer);
	data = (char *)malloc(sizeof(char) *(chara + 1));
	if (data)
	{
		_strcpy(data, buffer);
		data[chara] = '\0';
		commands = command_maker2(data);
	}
	return (commands);
}
