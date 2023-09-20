#include "main.h"
/**
 * commands_getter - to get command for nonintractive mode
 * Description: for alx project simple shell
 * @prog: the program name
 * @file: the file passed after program
 * @argc: the number of arguments
 * Return: 0 on success
 */
char **commands_getter(char *prog, char *file, int argc)
{
    int active;
    char **commands;

    commands = NULL;
    active = _intractive_checker(argc);
    if (active == 0)
    {
        commands = file_getter(prog, file);
    }
    else
    {
        commands = pipe_getter();
    }
    if (commands == NULL)
    exit(0);
    return (commands);
}

/**
 * file_getter - to get command for nonintractive mode
 * Description: for alx project simple shell
 * @prog: the program name
 * @file: the file passed after program
 * Return: 0 on success
 */
char **file_getter(char *prog, char *file)
{
    size_t bytes = 0;
    struct stat file_st;
    char **commands = NULL, *data = NULL;
    int flag;

    flag = stat(prog, &file_st);
    if (flag != -1)
    {
        commands = file_getter_helper(file_st, prog, data, bytes);
        if (!commands)
        {
            free (commands);
            return (NULL);
        }
    	return (commands);
    }
    else
    {
        printf("%s: 0: can't open %s", file, prog);
        exit(127);
    }
    return (NULL);
}
/**
 * file_getter_helper - to get command for nonintractive mode
 * Description: for alx project simple shell
 * @file_st: file statues
 * @fd: file describtor
 * @prog: the program name
 * @data: file's data
 * @bytes: number of bytes written inside the file
 * Return: 0 on success
 */
char **file_getter_helper(struct stat file_st, char *prog, char *data, size_t bytes)
{
	int fd;
    char **commands = NULL;

    if (S_ISREG(file_st.st_mode))
    {
        fd = open(prog, O_RDONLY);
        if (fd  == -1)
            exit(-1);
        if (file_st.st_size == 0)
		    exit(0);
	data = malloc((file_st.st_size + 1) * sizeof(char));
		if (!data)
        {
            free(data);
            return (NULL);
        }
        bytes = read(fd, data, file_st.st_size);
        if ((int) bytes == -1)
        perror("read");
        close(fd);
        data[bytes - 1] = '\0';
        if (data)
        commands = command_maker2(data);
        return (commands);
	}
    else
	exit(0);
}
/**
 * command_maker2 - to get command for nonintractive mode
 * Description: for alx project simple shell
 * @data: file's data
 * Return: 0 on success
 */
char **command_maker2(char *data)
{
    unsigned int i = 0, char_count = 0, x = 0;
    char *first_data, *command, **commands = NULL;

	while (*data != '\0')
	{
        if (*data == '\n')
        x++;
		data++;
	}
	char_count = x + 1;
	commands = (char **)malloc(sizeof(char *) *(char_count + 1));
	first_data = strtok(data, "\n");
	command = _strdup(first_data);
	commands[i++] = command;
	while (first_data)
	{
		first_data = strtok(NULL, "\n");
		if (first_data)
		{
			command = _strdup(first_data);
			commands[i++] = command;
		}
	}
	free(data);
	commands[i] = NULL;
	return (commands);
}
