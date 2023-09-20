#include "main.h"
/**
 * f_e - to excute some functions
 * Description: for alx project simple shell
 * @command: number of arguments
 * @com_arg: array of strings contains the arguments passed
 * @now: an argument
 * @i: an argument
 * @exit_st: an int argument
 * @commands: an argument
 * @enviroment: array of strings contains env variables
 * Return: 0 on success
 */
int f_e(char *command, char **com_arg, _path *now, int i,
int *exit_st, _path *enviroment, char **commands)
{
	int x = 0, flag = -30;
	char *functions[] = {"env", "exit"};

	while (x < 2)
	{
		if (_strcmp(functions[x], com_arg[0]) == 0)
		{
			flag = x;
			break;
		}
		x++;
	}
	if (flag == -30)
		return (-1);
	if (flag == 0)
		envv(exit_st);
	if (flag == 1)
		exitt(command, com_arg, now, i, exit_st, enviroment, commands);
	return (0);
}
/**
* envv - prints env
* @exit_st: an argument
* Return: nothing
*/
void envv(int *exit_st)
{
int n = 0;
char *env_var;
int f = fileno(stdout);

while (environ[n] != NULL)
{
env_var = environ[n];
write(f, env_var, _strlen(env_var));
write(f, "\n", 1);
n++;
}
*exit_st = 0;
}
/**
 * exitt - to excute exit function
 * Description: for alx project simple shell
 * @command: number of arguments
 * @com_arg: array of strings contains the arguments passed
 * @now: an argument
 * @i: an argument
 * @exit_st: an argument
 * @commands: an argument
 * @enviroment: array of strings contains env variables
 * Return: 0 on success
 */
void exitt(char *command, char **com_arg, _path *now,
int i, int *exit_st, _path *enviroment, char **commands)
{
if (com_arg[1] == NULL)
{
if (commands)
{
free(commands[i]);
if (commands)
free(commands);
}
free_list(enviroment);
free_list(now);
free_command(command, com_arg);
exit(*exit_st);
}
}
