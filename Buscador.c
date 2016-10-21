void buscarArchivo(char* arch, char* paths[], char* execPath){
	char returnPath[50];
	int result;
	char searchDir[50] = "";
	char* archivo;
	strcpy(returnPath, arch);
	
	if(arch[0] == '/' || (arch[0] == '.' && arch[1] == '.' && arch[2] == '/')){
		char* dir;
		char* nextDir;
		int pathReady = 0; 
		
		if(arch[0] == '/')
			searchDir[0] = '/';
		dir = strtok(arch,"/");
		nextDir = strtok(NULL,"/");
		
		if(nextDir != NULL) 
			strcat(searchDir,dir);
		else{
			nextDir = dir; 
			pathReady = 1;
		}

		while((nextDir != NULL) && !pathReady){
			dir = nextDir;
			nextDir = strtok(NULL,"/");
			strcat(searchDir,"/");
			if(nextDir != NULL)
				strcat(searchDir,dir);
		}
		archivo = dir;
	}
	
	else if(arch[0] == '.' && arch[1] == '/'){ 
		getcwd(searchDir, 50);
		strcat(searchDir,"/");
		archivo = strtok(arch, "/");
		archivo = strtok(NULL,"/");
	}
	
	else{
	
		int i;
		char aux[50];
		for(i = 0; i < 20; i++){
			if(paths[i] == NULL)
				break;
			strcpy(aux,paths[i]);
			strcat(aux,"/");
			strcat(aux,arch);
			result = access(aux, F_OK);
			if(!result){
				strcpy(execPath, aux);
				return;
			}
		}
		execPath[0] = 'X';
		return;
	}
	
	strcat(searchDir, archivo);
	result = access(searchDir, F_OK);
	if(!result)
		strcpy(execPath, searchDir);
	else
		execPath[0] = 'X';
}

void salida(char nombreArchivo[]){
	int fid;
	int banderas,permiso;
	banderas = O_WRONLY|O_CREAT|O_TRUNC;
	permiso = S_IWUSR|S_IRUSR;
	
	fid = open(nombreArchivo, banderas, permiso);	
	if (fid<0) {
		perror("open");
		exit(1);
	}
	close(STDOUT_FILENO);
	if (dup(fid)<0) {
		perror("dup");
		exit(1);
	}
	close(fid);
	}