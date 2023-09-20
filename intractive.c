#include "main.h"
/**
 * command_getter - code for intractive mode in shell
 * Description: for alx project simple shell
 * @now: holds the current path
 * Return: the command
 */

char *command_getter(_path *now)
{
	char *command = NULL;
	ssize_t bytes = 0;
	size_t i = 0;

	bytes = getline(&command, &i, stdin);
	if (bytes == -1)
	{
		free(command);
		free_list(now);
		if (bytes == EOF)
		{
			_putchar('\n');
			exit(0);
		}
		else
		{
			perror("getline");
			exit(1);
		}
	}
	else if (bytes > 0)
	{
		if (bytes == 1 && command[0] == '\n')
		{
			free(command);
			return (NULL);
		}
		command[bytes - 1] = '\0';
	}
	return (command);
}
/**
 * command_excuter - code for excute commands in shell
 * Description: for alx project simple shell
 * @command_arg: command arg
 * @enviroment: env
 * @exit_st: exit
 * @now: now
 * @argv: argv
 * Return: the command
 */
void command_excuter(char **command_arg, char **enviroment,
		int *exit_st, _path *now, char **argv)
{
	pid_t id;

	if (access(command_arg[0], X_OK) == 0)
	{
		id = fork();
		if (id == -1)
		{
			perror("fork");
			exit(1);
		}
		if (id == 0)
		{
			if (execve(command_arg[0], command_arg, enviroment) == -1)
			exit(126);
		}
		else if (id > 0)
		{
			waitpid(id, exit_st, WUNTRACED);
			*exit_st = WEXITSTATUS(*exit_st);
		}
	}
	else
	{
		error_handler(command_arg, enviroment, exit_st, now, argv);
	}
}
/**
 * command_arg_getter - code getting command with flags
 * Description: for alx project simple shell
 * @command: the command passed
 * @exit_st: the exit status;
 * Return: the command
 */
char **command_arg_getter(char *command, int exit_st)
{
	char *temp, *first_com, *f_command, *x, **com_arg;
	pid_t pid;
	int spaces, i = 0, flag1, flag2;

	temp = _strdup(command);
	if (!temp)
	return (NULL);
	spaces = letter_counter(temp, ' ');
	com_arg = malloc(sizeof(char *) * (spaces + 1));
	if (!com_arg)
	{
		free(com_arg);
		perror("malloc");
		return (NULL);
	}
	first_com = strtok(temp, " \t\r\n\a\"");
	if (!first_com)
	{
		free(com_arg);
		free(temp);
		f_command = NULL;
	}
	else
	{
		f_command = command_maker(first_com, command, com_arg, exit_st);
		com_arg[i++] = f_command;
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
				com_arg[i++] = f_command;
			}
		}
	}
	com_arg[i] = NULL;
	free(temp);
	return (com_arg);
}
/**
 * command_maker - process the command for excution
 * Description: for alx project simple shell
 * @first_com: the first part of the command
 * @command: the command passed
 * @com_arg: the commands with arguments
 * @exit_st: the exit status;
 * Return: the command
 */
char *command_maker(char *first_com, char *command,
		char **com_arg, int exit_st)
{
	char *temp = command, *pid_str, *x;
	pid_t pid;
	int flag1, flag2;

	if (first_com == NULL)
	{
		free(temp);
		free(com_arg);
		return (NULL);
	}
	flag1 = _strcmp(first_com, "$$");
	flag2 = _strcmp(first_com, "$?");
	if (flag1 == 0)
	{
		pid = getpid();
		pid_str = itos(pid);
	}
	else if (flag2 == 0)
		pid_str = itos(exit_st);
	else if (first_com[1] && first_com[0] == '$')
	{
		x = getenv(&first_com[1]);
		if (!x)
		{
		   pid_str = _strdup("");
		}
		else
		{
			pid_str = _strdup(x);
		}
	}
	else
	pid_str = _strdup(first_com);

	return (pid_str);
}
/**
 * error_handler - process the command for excution
 * Description: for alx project simple shell
 * @command_arg: command
 * @enviroment: environment
 * @exit_st: exitt
 * @now: n
 * @argv: argv
 * @exit_st: the exit status;
 * Return: the command
 */
void error_handler(char **command_arg, char **enviroment,
		int *exit_st, _path *now, char **argv)
{
	char *path_new;
	pid_t id;

	path_new = access_checker(command_arg[0], now);
	if (path_new)
	{
		id = fork();
		if (id == -1)
		{
			perror("fork");
			exit(1);
		}
		if (id == 0)
		{
			if (execve(command_arg[0], command_arg, enviroment) == -1)
				exit(126);
		}
		else if (id > 0)
		{
			waitpid(id, exit_st, WUNTRACED);
			*exit_st = WEXITSTATUS(*exit_st);
		}
		free(path_new);
	}
	else
	{
		if (access(command_arg[0], F_OK) == 0)
		{
			printf("error\n");
			*exit_st = 126;
		}
		else
		{
			printf("error 2%s\n", argv[0]);
			*exit_st = 127;
		}
	}
}
