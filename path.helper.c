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
