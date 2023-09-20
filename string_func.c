#include "main.h"
/**
 * _putchar - print character
 * Description: print a single character and send number of bytes written
 * @c: a signle char
 * Return: 1 on sucess
*/

int _putchar(char c)
{
	unsigned int i;

	i = write(1, &c, 1);
	return (i);
}
/**
 * _strlen - calulate the length of string
 * Description: for alx project simple shell
 * @s: '*s' is a pointer
 * Return: length of string
 */
int _strlen(char *s)
{
	int length = 0;

	while (s[length])
	{
		length++;
	}
	return (length);
}
/**
 * letter_counter - count how many c in str
 * Description: for alx project simple shell
 * @c: c is a special character
 * @str: is the string
 * Return: number of char in string
 */
int letter_counter(char *str, char c)
{
	int counter = 0;

	while (*str != '\0')
	{
		if (*(str + 1) == c && *str != c)
		{
			counter++;
		}
		str++;
	}
	counter++;
	return (counter);
}

/**
 * _strcmp - compares strings
 * Description: for alx project simple shell
 * @s1: '*s1' is a pointer
 * @s2: '*s2' is a pointer
 * Return: Always 0.
 */
int _strcmp(char *s1, char *s2)
{
while (*s1 && *s2)
{
if (*s1 != *s2)
{
return (*s1 - *s2);
}
s1++;
s2++;
}
if (*s1 == *s2)
return (0);
else
return (*s1 - *s2);
}
/**
 * itos - convert int to string
 * Description: for alx project simple shell
 * @pid: is the integer to be converted.
 * Return: Always 0.
 */
char *itos(int pid)
{
	int length, temp = pid;
	char *str;

	if (pid == 0)
	length = 1;
	else
	{
		for (length = 0; temp != 0; length++)
			temp = temp / 10;
	}
	length++;
	str = malloc(sizeof(char) * length);
	if (!str)
	{
		free(str);
		return (NULL);
	}
	length--;
	str[length] = '\0';
	while (length != 0)
	{
		length--;
		str[length] = pid % 10 + '0';
		pid = pid / 10;
	}
	return (str);
}
