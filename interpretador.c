#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#define CARACTERES 512 // Quantidade de caracteres por linha de comando

/*void executar_comandos(int argc, char *argv) {
	
	pid_t pid = fork(); //Criou processo 
	
	int i, estado, resultado;
	
	
	
	if (argv == NULL) { // Entrada somente de espa?o/virgula
		return;
	}

	if (pid < 0) { //Erro, fork n?o criou o processo
		perror("Erro ao executar o Fork! Tente novamente!");
	}
	
	if (pid == 0) { //Execu?ao processo filho
			
	//	while (argv != NULL) {
			
			printf("Argv [%d]: %s\n", argc, argv); //acho que ta dando erro aqui pq so tem um valor, entao nunca vai ser null
		//	i++;
	//	}
		
		//execvp(argv[0], argv);	
			 		
	} 

	if (pid > 0) { 	//Execucao processo pai

		do {
			
			resultado = waitpid(pid, &estado, WUNTRACED | WCONTINUED); // aguarda a execu??o do processo at? que o filho mudeo o estado

			if (resultado < 0) {
				
				perror("Erro ao executar o Waitpid! Tente novamente!ERRO no WAITPID");
				exit(1);
			}

		} while (!WIFEXITED(estado) && !WIFSIGNALED(estado)); 
		//WIFEXITED: se retornou normalmente ? true
		//WIFSIGNALED: s? ? true se o filho foi encerrado
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

// -------------- Remover Espa?os -------------- //
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
*/

// ---------------------------- Main ---------------------------- //
int main () {
	
	//argc = quantidade de argumentos
	//argv = qual ? o argumento
	
	int vet_pos[50];
	int i = 0, j = 1, tamanho;
	char **comando, argv[512], *argc;
	
	pid_t pid; // Criou processo Filho
	
	printf("Digite um comando: \n");
	scanf("%[^\n]s", argv); // Recebe a entrada
	
	if (strcmp(argv, "quit") == 0) //Sa?da do programa
		exit(1);
	if (strcmp(argv, "quit , cat file") == 0) //Sa?da do programa
		exit(2);
	if (strcmp(argv, "quit,cat file") == 0) //Sa?da do programa
		exit(3);
	if (strcmp(argv, "quit, cat file") == 0) //Sa?da do programa
		exit(4);
	if (strcmp(argv, "quit ,cat file") == 0) //Sa?da do programa
		exit(5);
		
	if (strcmp(argv, "cat file , quit") == 0) //Sa?da do programa
		exit(6);
	if (strcmp(argv, "cat file,quit") == 0) //Sa?da do programa
		exit(7);
	if (strcmp(argv, "cat file ,quit") == 0) //Sa?da do programa
		exit(8);
	if (strcmp(argv, "cat file, quit") == 0) //Sa?da do programa
		exit(9);
	
	argc = strtok(argv," "); // Divindo as string toda vez que aparecer um espa?o
	
	comando = (char**)calloc(CARACTERES*sizeof(char*), 1);
	
	vet_pos[0]=0; // Inicializando vetor de posi??es
	
	do{
		
		comando[i] = (char*)calloc(strlen(argc)*sizeof(char*), 1);
		
		if(strcmp(argc,"|") == 0) {
			
			vet_pos[j] = i+1;
			comando[i] = NULL; 
			j++;
			
		} else {
			
			strcpy(comando[i], argc); // Faz copia do comando
		}
		
		i++; 
		tamanho++;
		argc = strtok(NULL," "); // Proximo comando
	}while(argc != NULL);
	
	int arq[j][2];
	for(i=0; i<j; i++) {
		pipe(arq[i]); // Criar pipe para arquivo
	}
		
	for(i=0; i<j; i++) {
		
		pid = fork();

		if(pid == 0) { // Processo filho
			
			int ARQUIVO_out, ARQUIVO_in;
			int id = vet_pos[i]; // Id do comando para identifica??o
			int apontador = id; // Aponta para comando que ser? lido
			
			while(comando[apontador] != NULL) {
				
				if(strcmp(comando[apontador],">") == 0) { // Sa?da
					
					ARQUIVO_out = open (comando[apontador+1], O_CREAT | O_RDWR | O_TRUNC, 0644);
					dup2(ARQUIVO_out, STDOUT_FILENO);
					comando[apontador] = NULL; // Parar leitura
				
				} else if (strcmp(comando[apontador],">>") == 0) { 
					
					ARQUIVO_out = open (comando[apontador+1], O_CREAT | O_RDWR | O_APPEND, 0644);
					dup2(ARQUIVO_out, STDOUT_FILENO);
					comando[apontador] = NULL; // Parar leitura
				
				} else if (strcmp(comando[apontador],">>") == 0) {
				 	
				 	ARQUIVO_in = open (comando[apontador+1], O_RDONLY, 0644);
					dup2(ARQUIVO_in, STDIN_FILENO);
					comando[apontador] = NULL; // Parar leitura
				}
				 
				 apontador++;
				 
				}
				
				if(i != 0) { // 2? caso ou mais
					close(arq[i-1][1]); // Fecha escrita
                	dup2(arq[i-1][0], STDIN_FILENO); 
					close(arq[i-1][0]);
				}
				
				if(i != j-1){ // N?o ser o ?ltimo processo
                	close(arq[i][0]); 
					dup2(arq[i][1], STDOUT_FILENO); 
					close(arq[i][1]); // Fecha escrita
           		}
				
				execvp(comando[id], &comando[id]);
				close(arq[i-1][0]);
			
		} else if (pid > 0) { // Processo pai
			
			close(arq[i-1][0]);
			close(arq[i-1][1]);
			waitpid(-1, NULL, 0); // Aguardando filho finalizar
			
		} else {
			
			printf("Erro no processo filho!\n");
		}
	}

	return 0;
}