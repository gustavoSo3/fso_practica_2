#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define chars 50

char lineas[12][chars];

int main(int argc, char *argv[]){
	
	int p;
	char user[20],pw[20];			
	
	FILE *fp =fopen("passwd.txt","r");
	int line=0;
	
	while(!feof(fp))
		if(fgets(lineas[line],chars,fp) !=NULL)
			line++;
	fclose(fp);
	
	
	printf("Pid de init es %s \n",argv[1]);
	
	while(1){

	printf("User:");
	scanf("%s",user);
	printf("Password:");
	scanf("%s",pw);
	char usrypass[44];
	strcat(usrypass,user);
	strcat(usrypass,":");
	strcat(usrypass,pw);
	for(int i =0;i<
	//aqui esta para validar con el archivo
	//validarla con archivo de pws.txt
	//si es correcta hace lo de abajo.
	p=fork();
		if(p==0)
			execlp("./sh","sh",argv[1],NULL);
			
	wait(NULL);
	
	}
}