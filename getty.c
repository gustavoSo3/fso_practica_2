#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_INPUT_CHAR_LEN 50
#define MAX_USERS_ALLOWED 12

int main(int argc, char *argv[])
{

	char user_credential_entries[MAX_USERS_ALLOWED][MAX_INPUT_CHAR_LEN];
	char user[MAX_INPUT_CHAR_LEN], pw[MAX_INPUT_CHAR_LEN];

	FILE *fp = fopen("passwd", "r");
	int read_lines = 0;

	while (!feof(fp))
		if (fgets(user_credential_entries[read_lines], MAX_INPUT_CHAR_LEN, fp) != NULL)
			read_lines++;
	fclose(fp);

	while (1)
	{
		printf("User:");
		scanf("%s", user);
		printf("Password:");
		scanf("%s", pw);

		char user_and_password[MAX_INPUT_CHAR_LEN * 2 + 2];
		strcat(user_and_password, user);
		strcat(user_and_password, ":");
		strcat(user_and_password, pw);
		strcat(user_and_password, "\n");

		int valid_credentials = 0;
		for (int i = 0; i < read_lines + 1; i++)
		{
			if (strcmp(user_and_password, user_credential_entries[i]) == 0)
				valid_credentials = 1;
		}
		if (valid_credentials)
		{
			pid_t p = fork();
			if (p == 0)
				execlp("./sh", "sh", argv[1], NULL);

			wait(NULL);
		}
		strcpy(user_and_password, "");
	}
}