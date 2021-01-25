#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<syslog.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/wait.h>

extern int escribir, leer;
extern pthread_t tid;

void manejador( int sig ){
	int estado;
	pid_t pid;

	if( sig == SIGCHLD ){
		syslog( LOG_INFO, "\nSe recibio la señal SIGCHLD en el servidor\n");
		pid = wait(&estado);
		printf("Termino el proceso: %d con estado: %d\n", pid, estado>>8);
		escribir = 0;
	}
	else if( sig == SIGUSR1 ){
		syslog( LOG_INFO, "\nSe recibio la señal SIGUSR1 en el servidor\n");
		escribir = 1;
	}
	else if( sig == SIGINT || sig == SIGTERM ){
		syslog( LOG_INFO, "\nSe recibio la señal SIGINT en el servidor\n");
		printf("Concluimos la ejecución de la aplicacion Servidor \n");
		leer = 0;
		fin = 1;
		closelog();
	}
}

void ini_signals( void ){
	if( signal( SIGCHLD, manejador ) == SIG_ERR ){
		syslog( LOG_ERR, "Error en el manejador\n");
		exit( EXIT_FAILURE );
	}
	if( signal( SIGINT, manejador ) == SIG_ERR ){
		syslog( LOG_ERR, "Error en el manejador\n");
		exit( EXIT_FAILURE );
	}
	if( signal( SIGUSR1, manejador) == SIG_ERR ){
		syslog( LOG_ERR, "Error en el manejador\n");
		exit( EXIT_FAILURE );
	}
	if( signal( SIGTERM, manejador) == SIG_ERR ){
		syslog( LOG_ERR, "Error en el manejador\n");
		exit( EXIT_FAILURE );
	}
}
