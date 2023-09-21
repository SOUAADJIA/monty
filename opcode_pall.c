#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * op_pall - Prints all the values on the stack, starting from the top.
 * @stack: A pointer to the top of the stack.
 * @line_number: The current line number in the Monty bytecode file.
 * Return: Nothing.
 */
void op_pall(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;

	(void)line_number; /* Unused parameter */

	while (temp != NULL)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
}

