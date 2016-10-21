int leerTeclado(char* argv[], char* cadena){
	int contadorPalabra = 0;	

	argv[0] = strtok(cadena, " \n");
	for(contadorPalabra = 1; contadorPalabra < 20; contadorPalabra++){
		argv[contadorPalabra] = strtok(NULL, " \n");
		if (argv[contadorPalabra] == NULL)
			break;
	}
	return contadorPalabra;
}