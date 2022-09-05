#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define N_PROCESOS 6

pid_t p[N_PROCESOS];

void sighand(int sig)
{
	printf("Killing all child processes");
	for (int i = 0; i < N_PROCESOS; i++)
	{
		kill(p[i], SIGKILL);
	}
}

int main()
{

	char spid[5];

	pid_t pid = getpid();

	signal(SIGUSR1, sighand);

	sprintf(spid, "%d", pid);
	printf("Init pid %d \n", pid);

	for (int i = 0; i < N_PROCESOS - 1; i++)
	{
		p[i] = fork();
		if (p[i] == 0)
			execlp("xterm", "xterm", "-e", "./getty", spid, NULL);
	}
	while (1)
	{
		pid_t p_final = fork();
		if (p_final == 0)
			execlp("xterm", "xterm", "-e", "./getty", spid, NULL);
		wait(NULL);
	}

	return 0;
}