#include "main.h"
/**
 * _strdup - function to copy a string to another location
 * Description: for alx project simple shell
 * @str: 'size' is int recieved from another function
 * Return: 0 on success
 */
char *_strdup(char *str)
{
char *ptr;
int i;
int size = 0;

if (str == NULL)
return (NULL);
while (str[size] != '\0')
size++;
ptr = (char *)malloc((size + 1) * sizeof(char));
if (ptr != NULL)
{
for (i = 0; i <= size; i++)
{
ptr[i] = str[i];
}
return (ptr);
}
else
return (NULL);
}

/**
 * add_node - function that add node at a linked list
 * Description: for alx project simple shell
 * @head: an argument
 * @str: an argument
 * Return: 0 always
*/
_path *add_node(_path **head, const char *str)
{
	_path *new = malloc(sizeof(_path));

	if (!new)
	{
		free(new);
		return (NULL);
	}
	new->path = strdup(str);
	if (new->path == NULL)
	{
		free(new);
		return (NULL);
	}
	new->length = _strlen((char *)str);
	new->next = *head;
	*head = new;
	return (*head);
}
/**
 * free_list - function that free list
 * Description: for alx simple shell project
 * @head: an argument
 * Return: 0 always
*/
void free_list(_path *head)
{
	_path *buffer = head;
	_path *holder;

	if (!head)
	return;

	while (buffer->next != NULL)
	{
		holder = buffer;
		buffer = buffer->next;
		free(holder->path);
		free(holder);
	}
	free(buffer->path);
	free(buffer);
}

/**
 * access_checker - function that free list
 * Description: for alx simple shell project
 * @command_arg1: command arg
 * @now: now
 * Return: 0 always
*/

char *access_checker(char *command_arg1, _path *now)
{
	int length, counter, flag;
	char *f_path;

	counter = 0;
	if (!now)
	{
		return (NULL);
	}
	while (now != NULL)
	{
		length = _strlen(now->path) + _strlen(command_arg1) + 2;
		if (length > 1024)
		{
			write(STDERR_FILENO, "ERROR: Path Too Long\n", 21);
			continue;
		}
		f_path = (char *)malloc(sizeof(char) * length);
		_strcpy(f_path, now->path);
		_strcat(f_path, "/");
		_strcat(f_path, command_arg1);
		flag = access(f_path, X_OK);
		if (flag == 0)
		{
			counter = 1;
			break;
		}
		else
		{
			free(f_path);
		}
		now = now->next;
	}
	if (counter == 1)
		return (f_path);
	return (NULL);
}
