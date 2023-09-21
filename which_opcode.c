#include "monty.h"
/**
 * func - Pointers to functions
 * @tokens: opcode
 *
 * Return: function pointer or error handler
 */
void (*func(char *tokens))(stack_t **stack, unsigned int num_line)
{
	size_t i;

	instruction_t ops[] = {
		{"push", op_push},
		{"pall", op_pall},
		{"pint", op_pint},
		{"pop", op_pop},
		/*others*/
		{NULL, NULL}
	};

	size_t num_opcodes = sizeof(ops) / sizeof(ops[0]);

	for (i = 0; i < num_opcodes; i++)
	{
		if (strcmp(ops[i].opcode, tokens) == 0)
		{
			return (ops[i].f);
		}
	}

	return (NULL);
}
