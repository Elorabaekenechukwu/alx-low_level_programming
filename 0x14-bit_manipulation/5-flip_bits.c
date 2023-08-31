#include <stdio.h>
#include "main.h"
/**
  * flip_bits - a fxn dat returns d num of bit 2 flip 2 get frm 1 num 2 anoda.
  * @n: inputed figure 1 of unsigned long int.
  * @m: inputed figure 2 of unsigned long int.
  * Return: Flipped numbers
  */
unsigned int flip_bits(unsigned long int n, unsigned long int m)
{
	unsigned int flipped_numb = 0, fig, fig1;

	while (!(n == 0 && m == 0))
	{
		fig = n & 1;
		fig1 = m & 1;
		n = n >> 1;
		m = m >> 1;
		if (fig != fig1)
			flipped_numb += 1;
	}
	return (flipped_numb);
}

