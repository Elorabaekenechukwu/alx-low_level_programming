#include <stdio.h>
#include "main.h"
/**
  * get_endianness - a fxn that checks the endianness
  * Return: 0 if big endian, 1 if little endian
  */
int get_endianness(void)
{
	unsigned int j;
	char *a;

	j = 1;
	a = (char *) &j;

	return ((int)*a);
}

