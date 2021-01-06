#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include"defs.h"
#include"serial.h"
#include"procesamiento.h"

extern int leer, escribir;

void * leer_gps( void * arg ){
	int *pipefd = (int*)arg;
	char buffer[ TAM_BUFFER ], datos[ TAM_BUFFER ], dato;
	register int indice;
	int fd_serie;

	fd_serie = config_serial( "/dev/ttyS0", B9600 );
	while( leer ){
		indice = 0;
		dato = 0;
		memset( buffer, 0, TAM_BUFFER );
		while( dato != '\n' ){
			read( fd_serie, &dato, 1 );
 			buffer[ indice++ ] = dato; 	
		}
		buffer[ indice ] = '\0';

		if( !strncmp( "$GPGGA", buffer, 6 ) )
			obtener_datos(buffer, datos);
		if( escribir )
			write( pipefd[1], &datos, TAM_BUFFER );
	}
	close( pipefd[1] );

	pthread_exit( (void*) 0 );
}
