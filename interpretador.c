#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //Biblioteca do linux
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
int ContarVirgulas(char *li);
void remove_espaco(char *str);
void linha(char *linha, char **argumentos);

//================================= EXECUTAR COMANDO ==============================
void executarComandos(char *argv[]) {
	
	pid_t pid = fork(); //Criou processo filho
	int i;
	
	if (strcmp(argv[0], "quit") == 0) //saída do programa
		exit(EXIT_SUCCESS);
	
	if (argv[0] == NULL){ // Entrada somente de espaço/virgula
		return;
	}
	
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
//================================= CONTAR VIRGULA ==============================
int ContarVirgulas(char *li)
{
	int virgula = 0, i = 0;
	while (li[i] != '\0')
	{
		if (li[i] == ',')
		{
			virgula++;
		}
		i++;
	}
	return virgula;
}
//================================= APAGA ESPACO EM BRANCO ==============================
void remove_espaco(char *str) //apaga espaços em branco
{
	int i, j;
	for (i = 0; i < strlen(str) - 1; i++)
	{
		if (str[i] == ' ' && str[i + 1] == ' ')
		{
			for (j = i; j < strlen(str); j++)
			{
				str[j] = str[j + 1];
			}
			i--;
		}
	}
}

//================================= TRATAMENTO DAS LINHAS ==============================
void linha(char *linha, char **argumentos)
{
	//separa a string e armazena na variavel argumentos

	remove_espaco(linha);
	int i = 0;

	char *rest = NULL;
	char *token;

	token = strtok_r(linha, " ", &rest);

	while (token != NULL)
	{
		argumentos[i] = token;
		//printf("token: %s\n", token);
		token = strtok_r(NULL, " ", &rest);
		i++;
	}
	argumentos[i] = NULL;
}

int main (int argc, char *argv[]) {
	
	

	return 0;
}
