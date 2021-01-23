#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"defs.h"

void guardar_archivo( char *datos, char *archivo){
	FILE *apArch;

	apArch = fopen(archivo, "w");
	if( apArch == NULL ){
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}
	fprintf(apArch, "%s\n",datos);
	fclose( apArch );
}

void leer_archivo( char *datos, char *archivo ){
	FILE *apArch;
	
	apArch = fopen( archivo, "r");
	if( apArch == NULL ){
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}
	while( fscanf(apArch, "%s", datos) != EOF )
		if( !strncmp( "$GPGGA", datos, 6 ) )
			break;
	fclose( apArch );
}