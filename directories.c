#include "main.h"
/**
 * main - entry point for the program
 * Description: for alx project simple shell
 * Return: 0 on success
 */

_path *extract_directories()
{
	_path *path_list = NULL;
	char *path, *temp, *first_path;

	path = getenv("PATH");
	if (!path)
	{
		return (NULL);
	}
	temp = _strdup(path);
	if (!temp)
	{
		return (NULL);
	}
	first_path = strtok(temp, ":");
	while (first_path)
	{
		add_node(&path_list, first_path);
		first_path = strtok(NULL, ":");
	}
	free(temp);
	return (path_list);
}
