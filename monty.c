#include "monty.h"

/**
 * main - Entry point for the Monty interpreter.
 * @argc: The number of command-line arguments.
 * @argv: An array of strings containing the command-line arguments.
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	processMontyFile(argv[1]);

	return (EXIT_SUCCESS);
}

/**
 * processMontyFile - Process a Monty bytecode file.
 * @filename: The name of the Monty bytecode file.
 */
void processMontyFile(const char *filename)
{
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	unsigned int line_number = 0;
	stack_t *stack = NULL;
	char *opcode;

	file = fopen(filename, "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		exit(EXIT_FAILURE);
	}
	while (getline(&line, &len, file) != -1)
	{
		line_number++;
		opcode = strtok(line, " \t\n");
		if (opcode != NULL)
		{
			void (*handler)(stack_t **, unsigned int) = func(opcode);

			if (handler != NULL)
			{
				handler(&stack, line_number);
			}
			else
			{
				handleUnknownInstruction(opcode, line_number);
			}
		}
	}
	free(line);
	while (stack != NULL)
	{
		stack_t *temp = stack;

		stack = stack->next;
		free(temp);
	}
	fclose(file);
}

/**
 * tokenizeAndExecute - Tokenize and execute Monty instructions from a file.
 * @file: The Monty bytecode file.
 * @stack: A pointer to the top of the stack.
 */
void tokenizeAndExecute(FILE *file, stack_t **stack)
{
	char *line = NULL;
	size_t len = 0;
	unsigned int line_number = 0;
	char *opcode;

	while (getline(&line, &len, file) != -1)
	{
		line_number++;
		opcode = strtok(line, " \t\n");

		if (opcode != NULL)
		{
			void (*handler)(stack_t **, unsigned int) = func(opcode);

			if (handler != NULL)
			{
				handler(stack, line_number);
			}
			else
			{
				handleUnknownInstruction(opcode, line_number);
			}
		}
	}

	free(line);
}

/**
 * handleUnknownInstruction - Handle an unknown Monty instruction.
 * @opcode: The unknown opcode.
 * @line_number: The current line number in the Monty bytecode file.
 */
void handleUnknownInstruction(const char *opcode, unsigned int line_number)
{
	fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
	exit(EXIT_FAILURE);
}

