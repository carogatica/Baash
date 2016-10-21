#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include "Path.c"
#include "Buscador.c"
#include "Lector.c"
#include "Concurrencia.c"
#include "Pipe.c"


int main(int argc, char *argv[])
{
	int flagWaitPID, bgProcess, pipeExecuted;
	char* argv1[20]; 
	char* argv2[20];
	
	
	char hostname [20];
	gethostname(hostname,20);
	char* user;
	user = getlogin();
	
	pid_t pid;
	char comando [256]; 
	
	char *paths[20];
	int cantPath;
	cantPath = cadena_path(paths);

	char ejecutar[256];

	while(1)
	{
		strcpy(comando, "\n"); 
		flagWaitPID = 0;	  
		pipeExecuted = 0;

		printf("%s@%s:%s$ ", user, hostname,getcwd(NULL,50));

		fgets(comando,256,stdin);

		if(!strcmp(comando, "\n"))
		{
			printf("\n");
			continue;
		}

		else{
			argc = leerTeclado(argv, comando);
			
				
			if(!strcmp(comando,"exit"))
				return 0;

			if(!strcmp(argv[0],"cd"))
			{				
				chdir(argv[1]);
				continue;
			}
			
			int flagRedirect = 0;
			int doPipe = 0;
			char fileName[50];
			doPipe = chequearPipe(argv, argv1, argv2);
			flagRedirect = chequearRedireccion(argv, fileName);
			
			
			bgProcess = background(argv);
			if(bgProcess){
				argv[argc-1] = NULL;
				argv--;
			}
			
			buscarArchivo(argv[0], paths, ejecutar);
			if(ejecutar[0] == 'X')
				printf("El archivo no fue encontrado\n");
			else{
				pid = fork();
				if (pid<0) {
					perror("Creando el hijo");
					exit(1);
				}
				else if (pid == 0) {	

					if(flagRedirect == 2){
						salida(fileName);
					}
					else if(flagRedirect == 1){						
						freopen(fileName,"r",stdin);
					}
					else if(doPipe == 1){
						ejecutarPipeline(argv1, argv2, paths);
						pipeExecuted = 1;
					}
					if(!pipeExecuted){
						execv(ejecutar, argv);
						perror(ejecutar);
						exit(1);
					}
				}
				else{	
					flagWaitPID = -1;
				}
				if(bgProcess)
					waitpid(pid,&flagWaitPID,WNOHANG);
				else
					waitpid(pid,&flagWaitPID,0);
			}	
		}
	}
	return 0;
	}
