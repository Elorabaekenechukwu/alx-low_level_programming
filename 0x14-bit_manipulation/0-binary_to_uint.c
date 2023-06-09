#include <stdio.h>
#include "main.h"
/**
  * binary_to_uint - a fxn that converts a bin num to an unsigned int.
  * @b: a pointer to a string of 1 and 0 chars
  * Return: converted number, or if
  * -> there is one or more chars in the string b that is not 0 or 1
  * -> b is null
  */
unsigned int binary_to_uint(const char *b)
{
	unsigned int figure = 0;

	if (b == NULL)
		return (0);
	while (*b != '\0')
	{
	figure = figure << 1;
		if (*b != '1' && *b != '0')
			return (0);
		else if (*b == '1')
			figure = figure | 1;
		b++;
	}
	return (figure);
}
