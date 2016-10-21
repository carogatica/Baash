#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cadena_path (char* paths[])
{
	char * pPath = getenv ("PATH");
	int contadorPath;
	
	paths[0] = strtok(pPath, ":");
	
	for(contadorPath = 1; contadorPath< 20; contadorPath++)
	{
		paths[contadorPath] = strtok(NULL,":");		
		if (paths[contadorPath] == NULL)
			break;
	}
	
	strtok(NULL,":");
	return contadorPath+1;


}
