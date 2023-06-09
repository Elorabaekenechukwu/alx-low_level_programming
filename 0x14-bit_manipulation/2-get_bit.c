#include <stdio.h>
#include "main.h"
/**
  * get_bit - a fxn that returns the value of a bit at a given index.
  * @index: is the index, starting from 0 of the bit you want to get
  * @n: the inputed value
  * Return: the value of the bit at index index or -1 if an error occured
  */
int get_bit(unsigned long int n, unsigned int index);
{
	unsigned long int j;

	if (index > 63)
		return (-1);

	j = 1 << index;
	return ((n & j) > 0);
}
