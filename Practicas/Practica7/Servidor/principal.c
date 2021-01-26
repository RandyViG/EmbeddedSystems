#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<syslog.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include"defs.h"
#include"hilos.h"
#include"demonio.h"
#include"servidor.h"
#include"signal_handler.h"

int fin, leer, escribir;
pthread_t tid;

int main(int argc, char **argv){
	int sockfd, cliente_sockfd, pipefd[2];
	struct sockaddr_in direccion_servidor;
	pid_t pid;
	
	leer = 1;
	escribir = 0;
	fin = 0;

	ini_demonio();
	ini_signals();
	ini_servidor( &sockfd, &direccion_servidor );
	
	if( pipe( pipefd ) == -1 ){
		syslog(LOG_ERR, "Error al crear la tuberia...");
		exit( EXIT_FAILURE );
	}

	pthread_create( &tid, NULL, leer_rtcc, (void*)&pipefd );

	while( !fin ){
		syslog( LOG_INFO, "En espera de peticiones de conexión ...\n");
		if( ( cliente_sockfd = accept(sockfd, NULL, NULL) ) < 0 ){
			syslog( LOG_ERR, "Ocurrio algun problema al atender a un cliente");
			exit( EXIT_FAILURE );
		}
		pid = fork();
		if( !pid )
			atiende_cliente( cliente_sockfd , pipefd );
	}

	pthread_join( tid, NULL);
	
	close( sockfd );

	return 0;
}
