#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

#define MAX_INPUT_LEN 500

int n_args = 0;

char **get_arguments()
{

	char input[MAX_INPUT_LEN];
	n_args = 0;
	char **arguments = malloc(sizeof(char *));
	int i = 0;
	fflush(stdout);
	read(0, input, MAX_INPUT_LEN);
	int end_argument_i = 0;
	int start_argument_i = 0;

	// If we have an empty string as input
	if (*(input + i) == '\n' || *(input + i) == '\r')
	{
		strcpy(arguments[0], "");
		return arguments;
	}
	while (*(input + i) != '\n' && *(input + i) != '\r')
	{
		end_argument_i = i + 1;
		// If we have a space or end of line after a word, we create a new argument
		// and add it to the list of arguments
		if (*(input + i + 1) == ' ' || *(input + i + 1) == '\n' || *(input + i) == '\r')
		{
			char *new_argument = malloc(sizeof(char) * end_argument_i - start_argument_i + 1); //+1 to add \0
			strncpy(new_argument, input + start_argument_i, end_argument_i - start_argument_i);
			n_args++;
			arguments = realloc(arguments, sizeof(char *) * n_args);
			arguments[n_args - 1] = new_argument;
			start_argument_i = end_argument_i + 1;
		}
		i++;
	}
	// We add a NULL argument at the end
	arguments = realloc(arguments, sizeof(char *) * n_args + 1);
	arguments[n_args] = NULL;
	return arguments;
}

int main(int argc, char *argv[])
{
	int pid_init = atoi(argv[1]);
	int salir = 0;
	while (!salir)
	{
		printf(">");
		char **cmd = get_arguments();
		if (strcmp(cmd[0], "exit") == 0)
			salir = 1;
		else if (strcmp(cmd[0], "shutdown") == 0)
			kill(pid_init, SIGUSR1);
		else
		{
			int sh_p; // subprocess
			sh_p = fork();
			if (sh_p == 0)
			{
				execvp(cmd[0], cmd);
			}
			else
			{
				// here we decide if we run it in first or second plane
				if (strcmp(cmd[n_args - 1], "&") != 0)
					wait(NULL);
			}
		}
	}
	printf("Bye \n");
	exit(0);
}
