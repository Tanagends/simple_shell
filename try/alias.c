#include "zimbo.h"
/**
 * free_list - frees a list.
 * @head: initial node pointer pointer.
 */
void free_list(alist *head)
{
	alist *new;

	while (head != NULL)
	{
		new = head;
		head = head->next;
		free(new->name);
		free(new->alis);
		free(new);
	}
}
/**
 * add_node_end - adds node to a list.
 * @head: initial node pointer pointer.
 * @name: command name.
 * @alis: its alias.
 * Return: added node pointer.
 */
alist *add_node_end(alist **head, const char *name, const char *alis)
{
	list_t *ptr, *p;
	size_t i = 0;

	ptr = malloc(sizeof(alist));
	if (ptr == NULL)
		return (NULL);
	while (str[i++] != '\0')
		;
	ptr->name = strdup(name);
	ptr->alis = strdup(alis);
	if (ptr->str == NULL && ptr->alis == NULL)
	{
		free(ptr);
		return (NULL);
	}
	ptr->len = i - 1;
	ptr->next = NULL;
	if (*head == NULL)
		*head = ptr;
	else
	{
		p = *head;
		while (p->next != NULL)
			p = p->next;
		p->next = ptr;
	}
	return (ptr);
}
