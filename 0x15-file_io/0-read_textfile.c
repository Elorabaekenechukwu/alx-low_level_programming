#include <stdio.h>
#include <stdlib.h>
#include "main.h"
/**
  * read_textfile - a fxn dat reads a txt file & prints it 2 d posix stdout.
  * @letters: is the number of letters it should read and print
  * @filename: a pointer to a file named.
  * Return: d act num of lett it cud read & print bt if Null | failed return 0.
  */
ssize_t read_textfile(const char *filename, size_t letters)
{
	ssize_t a, b, c;
	char *kene;

	if (filename == NULL)
		return (0);

	kene = malloc(sizeof(char) * letters);
	if (kene == NULL)
		return (0);

	a = open(filename, O_RDONLY);
	b = read(a, kene, letters);
	c = write(STDOUT_FILENO, kene, b);

	if (a == -1 || b == -1 || c == -1 || c != b)
	{
		free(kene);
		return (0);
	}

	free(kene);
	close(a);

	return (c);
}
