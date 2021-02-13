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
	//argv = qual é o argumento
	
	char *comando = (char*)malloc(512*sizeof(char));
	if(comando != NULL)
	{
		printf("não alocado\n");
	}
	printf("Digite um comando: \n");
	
	//Contar virgulas. Mudar os paramentos para argc e argv
	do{
		
		//tratar antes de receber
		fgets(comando, 512, stdin);
		
			pid_t pid = fork(); //Criou processo 
	
	int i, estado, resultado;
	
	if (strcmp(comando, "quit") == 0) //Saída do programa
		exit(1);
	
	if (comando[0] == NULL) { // Entrada somente de espaço/virgula
		return;
	}

	if (pid < 0) { //Erro, fork não criou o processo
		perror("Erro ao executar o Fork! Tente novamente!");
	}
	
	if (pid == 0) { //Execuçao processo filho
			
		while (comando[i] != NULL) {
			
			printf("Argv [%d]: %s\n", i, comando[i]);
			i++;
		}
		
		//execvp(argv[0], argv);	
			 		
	} 

	if (pid > 0) { 	//Execucao processo pai

		do {
			
			resultado = waitpid(pid, &estado, WUNTRACED | WCONTINUED); // aguarda a execução do processo até que o filho mudeo o estado

			if (resultado < 0) {
				
				perror("Erro ao executar o Waitpid! Tente novamente!ERRO no WAITPID");
				exit(1);
			}

		} while (!WIFEXITED(estado) && !WIFSIGNALED(estado)); 
		//WIFEXITED: se retornou normalmente é true
		//WIFSIGNALED: só é true se o filho foi encerrado
		//Enquanto for diferente de verdade ele fica no loop
	}
		
	}while(1);


	return 0;
}
