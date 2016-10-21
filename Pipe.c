int chequearRedireccion(char* argv[], char nombreArchivo[]){
	int i;
	for (i = 0; i < 20; i++){
			
		if(argv[i] == NULL){
			nombreArchivo = NULL;
			return 0;
		}
		else if (!strcmp(argv[i], "<")){
			strcpy(nombreArchivo, argv[i+1]);
			argv[i] = NULL;		
			argv[i+1] = NULL;
			return 1;
		}
		else if (!strcmp(argv[i], ">")){
			strcpy(nombreArchivo, argv[i+1]);
			argv[i] = NULL;	
			argv[i+1] = NULL;
			return 2;
		}
	}
	return 0;
}



int chequearPipe(char* argv[], char* argv1[], char* argv2[]){
	int indexArg, aux, indexArg2;
	
	for(indexArg = 0; argv[indexArg] != NULL; indexArg++){
		aux = strcmp("|", argv[indexArg]);
		if(aux == 0)
			break;
		argv1[indexArg] = (char*) malloc ( strlen(argv[indexArg] + 1) ) ;
		strcpy(argv1[indexArg], argv[indexArg]);
	}
	argv1[indexArg] = '\0';
	

	if(argv[indexArg] == NULL)
		return 0;
	
	indexArg++;
	
	for(indexArg2 = 0; argv[indexArg] != NULL; indexArg2++){
		
		if(argv[indexArg] == NULL)
			break;
		argv2[indexArg2] = (char*) malloc ( strlen(argv[indexArg] + 1) ) ;
		strcpy(argv2[indexArg2], argv[indexArg]);
		indexArg++;
	}
	argv2[indexArg2] = '\0';
	
	return 1;
}

void ejecutarPipeline(char* argv1[], char* argv2[], char* paths[]){
	char ejecutaPath[256];
	
	int fd[2];
	pipe(fd);
	if (fork()==0) { 
		close(fd[0]);
		dup2(fd[1],1); 
		close(fd[1]);
		buscarArchivo(argv1[0], paths, ejecutaPath);
		execv(ejecutaPath, argv1);
		perror(ejecutaPath);
		exit(1);
	} 
	else {
		close(fd[1]); 
		dup2(fd[0],0);
		close(fd[0]);
		buscarArchivo(argv2[0], paths, ejecutaPath);
		execv(ejecutaPath, argv2);
		perror(ejecutaPath);
		exit(1);
	}
}
