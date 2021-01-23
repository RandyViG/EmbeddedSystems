#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/wait.h>

extern int sockfd, escribir, leer;
extern pthread_t tid;

void manejador( int sig ){
	int estado;
	pid_t pid;

	if( sig == SIGCHLD ){
		printf("\nSe recibio la señal SIGCHLD en el servidor\n");
		pid = wait(&estado);
		printf("Termino el proceso: %d con estado: %d\n", pid, estado>>8);
		escribir = 0;
	}
	else if( sig == SIGUSR1 ){
		printf("\nSe recibio la señal SIGUSR1 en el servidor\n");
		escribir = 1;
	}
	else if( sig == SIGINT ){
		printf("\nSe recibio la señal SIGINT en el servidor\n");
		printf("Concluimos la ejecución de la aplicacion Servidor \n");
		leer = 0;
		pthread_join( tid, NULL );
		close( sockfd );
		exit( 0 );
	}
}

void ini_signals( void ){
	if( signal( SIGCHLD, manejador ) == SIG_ERR ){
		perror("Error en el manejador");
		exit( EXIT_FAILURE );
	}
	if( signal( SIGINT, manejador ) == SIG_ERR ){
		perror("Error en el manejador");
		exit( EXIT_FAILURE );
	}
	if( signal( SIGUSR1, manejador) == SIG_ERR ){
		perror("Error en el manejador");
		exit( EXIT_FAILURE );
	}
}
