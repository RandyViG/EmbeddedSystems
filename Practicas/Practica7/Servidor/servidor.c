#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<syslog.h>
#include<signal.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include"defs.h"

void ini_servidor( int *sockfd, struct sockaddr_in * direccion_servidor ){
	memset( direccion_servidor, 0, sizeof(struct sockaddr_in) );
	direccion_servidor->sin_family = AF_INET;
	direccion_servidor->sin_port = htons(PUERTO);
	direccion_servidor->sin_addr.s_addr = INADDR_ANY;

	printf("Creando Socket ....\n");
	if( ( *sockfd = socket(AF_INET, SOCK_STREAM, 0) ) < 0 ){
		syslog( LOG_ERR, "Ocurrio un problema en la creacion del socket\n");
		exit( EXIT_FAILURE );
	}
	printf("Configurando socket ...\n");
	if( bind( *sockfd, (struct sockaddr *)direccion_servidor, sizeof(struct sockaddr_in) ) < 0 ){
		syslog( LOG_ERR, "Ocurrio un problema al configurar el socket\n");
		exit(EXIT_FAILURE );
	}
	printf("Estableciendo la aceptacion de clientes...\n\n");
	if( listen(*sockfd, COLA_CLIENTES) < 0 ){
		syslog( LOG_ERR, "Ocurrio un problema al crear la cola de aceptar peticiones de los clientes\n");
		exit( EXIT_FAILURE );
	}
}

void atiende_cliente( int cliente_sockfd, int pipefd[] ){
	char mensaje[TAM_BUFFER], *dia[]={"Lunes","Martes","Miercoles","Jueves","Viernes","Sabado","Domingo"};
	int datos[ N ];
	close( pipefd[1] );
	syslog( LOG_INFO, "Se aceptó un cliente, atendiendolo \n");
	kill( getppid(), SIGUSR1 );
	read( pipefd[0], datos, sizeof(int) * N );
	sprintf( mensaje , "Hora: %x:%x:%x  Fecha: %s %d-%d-%d", datos[2], datos[1], datos[0], dia[ datos[3] - 1 ], datos[4], datos[5], datos[6] );
	if( write(cliente_sockfd, mensaje, TAM_BUFFER) < 0 ){
		syslog( LOG_ERR, "Ocurrio un problema en el envio de un mensaje al cliente");
		exit( EXIT_FAILURE );
	}
	close( pipefd[0] );	
	close( cliente_sockfd );

	exit( 0 );
}
