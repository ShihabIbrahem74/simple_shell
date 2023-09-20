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
	data = (char *)malloc(sizeof(char) * (chara + 1));
	if (data)
	{
		_strcpy(data, buffer);
		data[chara] = '\0';
		commands = command_maker2(data);
	}
	return (commands);
}

/**
 * pipe_getter - to get command for nonintractive mode
 * @command: the command line
 * @first_com: the first come used with strtok
 * @com_arg: the command with arguments
 * @exit_st: handle the exit status
 * @i: pointer to integer
 * Description: for alx project simple shell
 * Return: 0 on success
 */
char **intractive_error_hanlder(char *command, char *first_com,
char **com_arg, int exit_st, int *i)
{
	char *x, *f_command;
	int flag1, flag2;
	pid_t pid;

	f_command = command_maker(first_com, command, com_arg, exit_st);
	com_arg[(*i)++] = f_command;
	while (first_com)
	{
		first_com = strtok(NULL, " \t\r\n\a\"");
		if (first_com)
		{
			flag1 = _strcmp(first_com, "$$");
			flag2 = _strcmp(first_com, "$?");
			if (flag1 == 0)
			{
				pid = getpid();
				f_command = itos(pid);
			}
			else if (flag2 == 0)
				f_command = itos(exit_st);
			else if (first_com[1] && first_com[0] == '$')
			{
				x = getenv(&first_com[1]);
				if (!x)
				f_command = _strdup("");
				else
				f_command = _strdup(x);
			}
			else
				f_command = _strdup(first_com);
			com_arg[(*i)++] = f_command;
		}
	}

	return (com_arg);
}
