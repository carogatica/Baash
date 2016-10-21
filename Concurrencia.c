int background(char* argv[]){
	int i;
	for(i = 0; i < 20; i++){
		if(argv[i] == NULL)
			break;
	}
	if(!strcmp(argv[i-1], "&"))
		return 1;
	return 0;
}