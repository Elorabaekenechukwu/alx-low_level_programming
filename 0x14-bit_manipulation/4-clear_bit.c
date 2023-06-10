#include <stdio.h>
#include "main.h"
/**
  * clear_bit - a fxn that sets the value of a bit to 0 at a given index.
  * @index: is the index, starting from 0 of the bit you want to set.
  * @n: inputed figure of the unsigned long int.
  * Return: 1 if it worked, or -1 if an error occurred
  */
int clear_bit(unsigned long int *n, unsigned int index)
{
	if (index > 63)
		return (-1);

	*n = *n & ~(1ul << index);
	return (1);
}
