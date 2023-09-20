#include "main.h"
/**
 * main - entry point for the program
 * Description: for alx project simple shell
 * @argc: number of arguments
 * @argv: array of strings contains the arguments passed
 * @enviroment: array of strings contains env variables
 *
 * Return: 0 on success
 */
int main(int argc, char **argv, char **enviroment)
{
	int status_int = 0, i, *exit_st = &status_int;
	char *command = NULL;
	char **command_arg = NULL, **commands = NULL;
	_path *now;

	if (_intractive_checker(argc) == 2 || _intractive_checker(argc) == 0)
		commands = commands_getter(argv[0], argv[1], argc);
	now = extract_directories();
	i = 1;
	while (++i)
	{
		if (_intractive_checker(argc) == 2 || _intractive_checker(argc) == 0)
		{
			if (commands[i - 1] != NULL)
			command = commands[i - 1];
			else
			{
				free(commands);
				break;
			}
		}
		if (_intractive_checker(argc) == 1)
		{
			_putchar('$');
			_putchar(' ');
			command = command_getter(now);
		}
		if (command == NULL)
			continue;
		command_arg = command_arg_getter(command, *exit_st);
		if (!command_arg)
		{
			free(command);
			continue;
		}
		command_excuter(command_arg, enviroment, exit_st, now, argv);
		free_command(command, command_arg);
	}
	free_list(now);
	exit(*exit_st);
}

/**
 * _intractive_checker - check what mode is the program
 * Description: for alx project simple shell
 * @argc: number of arguments
 *
 * Return: integer based on mode
 */
int _intractive_checker(int argc)
{
	int mode;

	if (argc == 1)
	{
		mode = isatty(STDIN_FILENO);
		if (mode)
		return (1);
		else
		return (2);
	}
	else if (argc > 1)
	return (0);

	return (-1);
}
/**
 * free_command - to avoid memory leaks
 * Description: for alx project simple shell
 * @command: command
 * @command_arg: commands with arguments
 * Return: void
 */
void free_command(char *command, char **command_arg)
{
free(command_arg);
free(command);
}
