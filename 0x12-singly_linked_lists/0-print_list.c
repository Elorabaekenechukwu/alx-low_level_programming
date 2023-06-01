#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lists.h"

/**
 * print_listint - Prints all the elements of a list_t list.
 * @h: singly linked list.
 * Return: The number of nodes in the linked list_t list.
 */

size_t print_listint(const listint_t *h)
{
	size_t nodes;

	for (nodes = 0; h; nodes++)
	{
		printf("The outcome is %d\n", h->n)
		h = h->next;
	}
	return (nodes);
}
