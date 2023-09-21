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

	if (processMontyFile(argv[1]) != EXIT_SUCCESS)
	{
		exit(EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}

/**
 * cleanupStack - Frees the memory allocated for the stack.
 * @stack: A pointer to the top of the stack.
 * Return: nothing
 */
void cleanupStack(stack_t **stack)
{
	while (*stack != NULL)
	{
		stack_t *temp = *stack;
		*stack = (*stack)->next;
		free(temp);
	}
}

/**
 * tokenizeAndExecute - Tokenize and execute Monty instructions from a file.
 * @file: The Monty bytecode file.
 * @stack: A pointer to the top of the stack.
 * Return: nothing
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
				handler(stack, line_number);
			else
				handleUnknownInstruction(opcode, line_number);
		}
	}

	free(line);
}

/**
 * handleUnknownInstruction - Handle an unknown Monty instruction.
 * @opcode: The unknown opcode.
 * @line_number: The current line number in the Monty bytecode file.
 * Return: nothing
 */
void handleUnknownInstruction(const char *opcode, unsigned int line_number)
{
	fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
	exit(EXIT_FAILURE);
}

/**
 * processMontyFile - Process a Monty bytecode file.
 * @filename: The name of the Monty bytecode file.
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int processMontyFile(const char *filename)
{
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	unsigned int line_number = 0;
	stack_t *stack = NULL;
	char *opcode;
	int result = EXIT_SUCCESS;

	file = fopen(filename, "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		return (EXIT_FAILURE);
	}
	while (getline(&line, &len, file) != -1)
	{
		line_number++;
		opcode = strtok(line, " \t\n");
		if (opcode != NULL)
		{
			void (*handler)(stack_t **, unsigned int) = func(opcode);

			if (handler != NULL)
				handler(&stack, line_number);
			else
			{
				handleUnknownInstruction(opcode, line_number);
				result = EXIT_FAILURE;
				break;
			}
		}
	}

	free(line);
	cleanupStack(&stack);
	fclose(file);

	return (result);
}

