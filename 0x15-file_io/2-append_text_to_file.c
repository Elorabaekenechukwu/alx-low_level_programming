#include "main.h"
#include <stdlib.h>
/**
  * append_text_to_file - a fxn dat appends text at the end of a file.
  * @filename: is the name of the file.
  * @text_content: is the NULL terminated string to add at the end of the file.
  * Return: 1 on success and -1 on failure
  */
int append_text_to_file(const char *filename, char *text_content)
{
	int a = 0, File;

	if (filename == NULL)
		return (-1);

	if (text_content == NULL)
		text_content = "";


	while (text_content[a] != '\0')
	{
		a++;
	}

	File = open(filename, O_WRONLY | O_APPEND);

	if (File == -1)
		return (-1);

	write(File, text_content, a);

	return (1);
}
