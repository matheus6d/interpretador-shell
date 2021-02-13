#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
int contar_virgulas(char *li);
void remove_espaco(char *str);
void linha(char *linha, char **argumentos);

// -------------- Main -------------- //
int main () {
	
	//argc = quantidade de argumentos
	//argv = qual � o argumento
	
	char *comando = (char*)malloc(512*sizeof(char));
	if(comando != NULL)
	{
		printf("n�o alocado\n");
	}
	printf("Digite um comando: \n");
	
	//Contar virgulas. Mudar os paramentos para argc e argv
	do{
		
		//tratar antes de receber
		fgets(comando, 512, stdin);
		
			pid_t pid = fork(); //Criou processo 
	
	int i, estado, resultado;
	
	if (strcmp(comando, "quit") == 0) //Sa�da do programa
		exit(1);
	
	if (comando[0] == NULL) { // Entrada somente de espa�o/virgula
		return;
	}

	if (pid < 0) { //Erro, fork n�o criou o processo
		perror("Erro ao executar o Fork! Tente novamente!");
	}
	
	if (pid == 0) { //Execu�ao processo filho
			
		while (comando[i] != NULL) {
			
			printf("Argv [%d]: %s\n", i, comando[i]);
			i++;
		}
		
		//execvp(argv[0], argv);	
			 		
	} 

	if (pid > 0) { 	//Execucao processo pai

		do {
			
			resultado = waitpid(pid, &estado, WUNTRACED | WCONTINUED); // aguarda a execu��o do processo at� que o filho mudeo o estado

			if (resultado < 0) {
				
				perror("Erro ao executar o Waitpid! Tente novamente!ERRO no WAITPID");
				exit(1);
			}

		} while (!WIFEXITED(estado) && !WIFSIGNALED(estado)); 
		//WIFEXITED: se retornou normalmente � true
		//WIFSIGNALED: s� � true se o filho foi encerrado
		//Enquanto for diferente de verdade ele fica no loop
	}
		
	}while(1);


	return 0;
}
