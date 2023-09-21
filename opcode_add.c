#include "monty.h"
#include <stdio.h>

/**
 * op_add - Adds the top two elements of the stack.
 * @stack: A pointer to the top of the stack.
 * @line_number: The current line number in the Monty bytecode file.
 * Return: Nothing.
 */
void op_add(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	temp = *stack;
	*stack = (*stack)->next;
	(*stack)->n += temp->n;
	(*stack)->prev = NULL;
	free(temp);
}

