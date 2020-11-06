#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //Biblioteca do linux
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

void executarComandos(char *argv[]) {
	
	pid_t pid = fork(); //Criou processo filho
	int i;
	
	//Erro, fork não criou o processo
	if (pid < 0) {
		perror("ERRO no FORK");
	}
	
	//Execuçao processo filho
	if (pid == 0) {
			
		while (argv[i] != NULL) {
			
			printf("Argv: %d: %s\n", i, argv[i]);
			i++;
		}
		
		execvp(argv[0], argv);	
			 		
	} 
	
	//Exeucao processo pai
	if (pid > 0) {
		
		int retorno, status;
		
		do {
			
			retorno = waitpid(pid, &status, WUNTRACED | WCONTINUED); // aguarda o processo filho

			if (retorno < 0)
			{
				perror("ERRO no WAITPID");
				exit(EXIT_FAILURE);
			}

		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		
	}
}

int main (int argc, char *argv[]) {
	
	teste

	return 0;
}
