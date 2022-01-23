#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXINPUTSIZE 2048

int main()
{
	while(1){
		char buf[MAXINPUTSIZE];
		printf("Enter your command: ");
		fgets(buf, MAXINPUTSIZE, stdin);
		int pos = 0;
		char* parsed = strtok(buf, " \n");
		char* parsed_arr[128];
		
		while (parsed != NULL)
		{
			parsed_arr[pos++] = parsed;
			parsed = strtok (NULL, " \n");
		}
		parsed_arr[pos] = NULL;
		
		if(strcmp(parsed_arr[0],"cd") == 0){
			int passed = chdir(parsed_arr[1]);
			if(passed == -1){
				perror("Error");
			}
		}else if(strcmp(parsed_arr[0],"exit") == 0){
			exit(0);
		}else{
			if(fork() == 0){
				if(execvp(parsed_arr[0], parsed_arr) < 0){
					perror("Error");
					exit(1);
				}
			}else{
				wait(NULL);
			}
		}
	}
}







