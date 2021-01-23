#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include"defs.h"
#include"hilos.h"
#include"servidor.h"
#include"signal_handler.h"

int sockfd, leer = 1, escribir = 0;
pthread_t tid;

int main(int argc, char **argv){
	int cliente_sockfd, pipefd[2];
	struct sockaddr_in direccion_servidor;
	pid_t pid;
	
	ini_signals();
	ini_servidor( &direccion_servidor );
	
	if( pipe( pipefd ) == -1 ){
		perror("Error al crear la tuberia...");
		exit( EXIT_FAILURE );
	}

	pthread_create( &tid, NULL, leer_gps, (void*)&pipefd );

	for( ; EVER ;  ){
		printf("En espera de peticiones de conexión ...\n");
		if( ( cliente_sockfd = accept(sockfd, NULL, NULL) ) < 0 ){
			perror("Ocurrio algun problema al atender a un cliente");
			exit( EXIT_FAILURE );
		}
		pid = fork();
		if( !pid )
			atiende_cliente( cliente_sockfd , pipefd );
	}

	return 0;
}
