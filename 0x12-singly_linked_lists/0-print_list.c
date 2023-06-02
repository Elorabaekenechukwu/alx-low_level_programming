#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lists.h"

/**
 * print_list - Prints all the elements of a list_t list.
 * @h: singly linked list.
 * Return: The number of nodes in the linked list_t list.
 */

size_t list_len(const list_t *h)
{
	size_t nodes;

	for (nodes = 0; h; nodes++)
	{
		printf("The outcome is %d\n", h->len);
		h = h->next;
	}
	return nodes;
}
