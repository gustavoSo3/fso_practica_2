#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define N_PROCESOS 6

int p[N_PROCESOS];

void sighand(int sig){
printf("aqui tenemos que terminar todos los procesos \n");
	for(int i=0;i<N_PROCESOS;i++){
		kill(p[i],9);
	}
	
}

int main(){
	
	char spid[5];
	int pid= getpid();
	
	signal(SIGUSR1,sighand);
	
	sprintf(spid,"%d",pid);
	printf("el pid de init es %d \n",pid);
	
	for(int i=0;i<N_PROCESOS - 1;i++){
		p[i]=fork();
		if(p[i]==0)
			execlp("xterm","xterm","-e","./getty",spid,NULL);
	}
	while(1){
		pid_t p_final = fork();
		if(p_final == 0)
			execlp("xterm","xterm","-e","./getty",spid,NULL);
		wait(NULL);
	}
	
	return 0;
}