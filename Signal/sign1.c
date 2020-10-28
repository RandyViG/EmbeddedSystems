#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

#define EVER 1

void manejador( int sig );

int main( void ){
	printf("Prubando señales...");	
	if( signal( SIGINT, manejador ) == SIG_ERR ){
		perror("Error en el manejador de SIGNINT...\n");
		exit( EXIT_FAILURE );
	}
	if( signal( SIGTERM, manejador ) == SIG_ERR ){
		perror("Error en el manejador de SIGNINT...\n");
		exit( EXIT_FAILURE );
	}

	for( ; EVER ;  )
		pause();

	return 0;
}

void manejador( int sig ){
	if( sig == SIGINT )
		printf("No voy a terminar...\n");
	if( sig == SIGTERM )
		printf("Que no entiendes que no voy a terminar...\n");
}
