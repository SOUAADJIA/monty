#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * op_pall - Removes the top element of the stack.
 * @stack: A pointer to the top of the stack.
 * @line_number: The current line number in the Monty bytecode file.
 * Return: nothing
 */
void op_pall(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pull an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	if ((*stack)->next != NULL)
	{
		temp = (*stack)->next;
		temp->prev = NULL;
		free(*stack);
		*stack = temp;
	}
	else
	{
		free(*stack);
		*stack = NULL;
	}
}
