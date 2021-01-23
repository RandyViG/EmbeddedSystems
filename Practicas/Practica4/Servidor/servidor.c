#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>

#include"defs.h"
#include"procesamiento.h"

extern int sockfd;

void ini_servidor( struct sockaddr_in * direccion_servidor ){
	memset( direccion_servidor, 0, sizeof(struct sockaddr_in) );
	direccion_servidor->sin_family = AF_INET;
	direccion_servidor->sin_port = htons(PUERTO);
	direccion_servidor->sin_addr.s_addr = INADDR_ANY;

	printf("Creando Socket ....\n");
	if( ( sockfd = socket(AF_INET, SOCK_STREAM, 0) ) < 0 ){
		perror("Ocurrio un problema en la creacion del socket\n");
		exit( EXIT_FAILURE );
	}
	printf("Configurando socket ...\n");
	if( bind( sockfd, (struct sockaddr *)direccion_servidor, sizeof(struct sockaddr_in) ) < 0 ){
		perror ("Ocurrio un problema al configurar el socket\n");
		exit(EXIT_FAILURE );
	}
	printf("Estableciendo la aceptacion de clientes...\n\n");
	if( listen(sockfd, COLA_CLIENTES) < 0 ){
		perror("Ocurrio un problema al crear la cola de aceptar peticiones de los clientes\n");
		exit( EXIT_FAILURE );
	}
}

void atiende_cliente( int cliente_sockfd ){
	char mensaje[TAM_BUFFER];
	printf("\nSe aceptó un cliente, atendiendolo \n");
	obtener_datos( mensaje );
	//datos( mensaje );
	if( write(cliente_sockfd, mensaje, TAM_BUFFER) < 0 ){
		perror("Ocurrio un problema en el envio de un mensaje al cliente");
		exit( EXIT_FAILURE );
	}	
	close( cliente_sockfd );

	exit( 0 );
}
