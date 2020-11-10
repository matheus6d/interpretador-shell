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
