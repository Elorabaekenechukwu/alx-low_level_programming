#include <stdio.h>
#include "main.h"
/**
  * print_binary - fxn that prints the bin representation of a number.
  * @n: unsigned long integer
  * Return: (0)
  */
void print_binary(unsigned long int n)
{
	if (n >> 0)
	{
		if (n >> 1)
			print_binary(n >> 1);
		_putchar((n & 1) + '0');
	}
	else
	{
		_putchar('0');
	}
}
