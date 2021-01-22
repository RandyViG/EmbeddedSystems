#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<netdb.h>

#define TAM_BUFFER 100

char * nslookup( char *hostname );

int main( int argc, char **argv ){
	if( argc < 3 ){
		perror("Use: %s host port");
		exit( EXIT_FAILURE );
	}
	int sockfd, puerto;
	struct sockaddr_in direccion_servidor;
	char mensaje[TAM_BUFFER], *host;
	
	puerto = atoi( argv[2] );
	
	memset (&direccion_servidor, 0, sizeof (direccion_servidor));
	direccion_servidor.sin_family = AF_INET;
	direccion_servidor.sin_port = htons(puerto);

	host = nslookup( argv[1] );
	
	if( inet_pton( AF_INET, host, &direccion_servidor.sin_addr ) <= 0 ){
		perror("Ocurrio un error al momento de asignar la direccion IP\n");
		exit( EXIT_FAILURE );
	}

	printf("Creando Socket ....\n");
	if( ( sockfd = socket( AF_INET, SOCK_STREAM, 0) ) < 0 ){
		perror("Ocurrio un problema en la creacion del socket\n");
		exit( EXIT_FAILURE );
	}

	printf("Estableciendo conexion ...\n");
	if( connect(sockfd, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor) ) < 0) {
		perror ("Ocurrio un problema al establecer la conexion\n");
		exit( EXIT_FAILURE );
	}

	printf("Recibiendo contestacion del servidor ...\n");
	if( read( sockfd, mensaje, TAM_BUFFER ) < 0){	
		perror ("Ocurrio algun problema al recibir datos del cliente\n");
		exit( EXIT_FAILURE );
	}
	
	printf("\nEl servidor envio el siguiente mensaje: \n%s\n\n", mensaje);
	printf("Cerrando la aplicacion cliente\n");

	close( sockfd );

	return 0;
}

char * nslookup( char *hostname ){
	struct addrinfo* res;
  	char* hostaddr;
  	struct sockaddr_in* saddr;
  
  	if ( getaddrinfo(hostname, NULL, NULL, &res) != 0 ) {
    	fprintf(stderr, "Error in resolving hostname %s\n", hostname);
    	exit( EXIT_FAILURE );
  	}

  	saddr = (struct sockaddr_in*)res->ai_addr;
  	hostaddr = inet_ntoa(saddr->sin_addr);
  	printf("Dirección ip para %s es: %s\n", hostname, hostaddr);
	
	return hostaddr;
}
