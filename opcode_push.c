#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
/**
 * op_push - Pushes an integer onto the stack
 * @stack: A pointer to the top of the stack
 * @line_number: The current line number in the Monty bytecode file
 * Return: nothing
 */
void op_push(stack_t **stack, unsigned int line_number)
{
	char *argument = strtok(NULL, " \n");
	int value = atoi(argument); /*Convert the argument to an integer*/
	stack_t *new_node;
	int i;

	if (argument == NULL)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	/* Check if the argument is a valid integer*/
	for (i = 0; argument[i] != '\0'; i++)
	{
		if (!isdigit(argument[i]) && argument[i] != '-')
		{
			fprintf(stderr, "L%d: usage: push integer\n", line_number);
			exit(EXIT_FAILURE);
		}
	}
	/*Create a new node for the stack*/
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	new_node->n = value;
	new_node->prev = NULL;
	if (*stack == NULL)
	{
		new_node->next = NULL;
		*stack = new_node;
	}
	else
	{
		new_node->next = *stack;
		(*stack)->prev = new_node;
		*stack = new_node;
	}
}
