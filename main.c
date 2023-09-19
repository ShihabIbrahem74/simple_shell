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
int main (int argc, char **argv, char **enviroment)
{
    int active, status_int = 0, i;
    int *exit_st = &status_int;
    char *command = NULL; 
    char **command_arg = NULL; /**commands = NULL*/
    _path *now;

    active = _intractive_checker(argc);
    /*if (active == 2 || active == 0)
    {
        commands = commands_getter(active, argv[0], argv[1])
    }*/
    now = extract_directories();
    i = 1;
    while (++i)
    {
        if (active == 1)
        {
            _putchar('$');
            command = command_getter(now);
        }
        if (command == NULL)
        {
            continue;
        }
        command_arg = command_arg_getter(command, *exit_st);
        if (!command_arg)
        {
            free(command);
            continue;
        }
        command_excuter(command_arg, enviroment, exit_st, now, argv);
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
int _intractive_checker (int argc)
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
