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

void executar_comandos(char *argv) {
	
	pid_t pid = fork(); //Criou processo 
	
	int i, estado, resultado;
	
	if (strcmp(argv, "quit") == 0) //Saída do programa
		exit(1);
	if (strcmp(argv, "quit , cat file") == 0) //Saída do programa
		exit(2);
	if (strcmp(argv, "quit,cat file") == 0) //Saída do programa
		exit(3);
	if (strcmp(argv, "quit, cat file") == 0) //Saída do programa
		exit(4);
	if (strcmp(argv, "quit ,cat file") == 0) //Saída do programa
		exit(5);
		
	if (strcmp(argv, "cat file , quit") == 0) //Saída do programa
		exit(6);
	if (strcmp(argv, "cat file,quit") == 0) //Saída do programa
		exit(7);
	if (strcmp(argv, "cat file ,quit") == 0) //Saída do programa
		exit(8);
	if (strcmp(argv, "cat file, quit") == 0) //Saída do programa
		exit(9);
	
	if (argv == NULL) { // Entrada somente de espaço/virgula
		return;
	}

	if (pid < 0) { //Erro, fork não criou o processo
		perror("Erro ao executar o Fork! Tente novamente!");
	}
	
	if (pid == 0) { //Execuçao processo filho
			
	//	while (argv != NULL) {
			
			printf("Argv [%d]: %s\n", i, argv); //acho que ta dando erro aqui pq so tem um valor, entao nunca vai ser null
		//	i++;
	//	}
		
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
}

// -------------- Contar Virgulas -------------- //
int contar_virgulas(char *li)
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

// -------------- Remover Espaços -------------- //
void remove_espaco(char *str) 
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

// -------------- Tratar linhas -------------- //
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

// -------------- Main -------------- //
int main (int argc, char *argv[]) {
	
	//argc = quantidade de argumentos
	//argv = qual é o argumento
	
	char *comando = (char*)malloc(512*sizeof(char));
	printf("Digite um comando: \n");
	
	//Contar virgulas. Mudar os paramentos para argc e argv
	do{
		
		//tratar antes de receber
		//fgets(comando, 512, stdin); //o fgets precisa de uns tratamentos de entrada
		gets(comando);
		executar_comandos(comando); 
		
		
	}while(1);


	return 0;
}
