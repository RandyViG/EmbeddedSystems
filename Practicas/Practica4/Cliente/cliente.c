#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PUERTO 5000
#define TAM_BUFFER 100
#define DIR_IP "127.0.0.1"

int main( int argc, char **argv ){
	int sockfd;
	struct sockaddr_in direccion_servidor;
	char mensaje[TAM_BUFFER];

	memset (&direccion_servidor, 0, sizeof (direccion_servidor));
	direccion_servidor.sin_family = AF_INET;
	direccion_servidor.sin_port = htons(PUERTO);

	if( inet_pton( AF_INET, DIR_IP, &direccion_servidor.sin_addr ) <= 0 ){
		perror("Ocurrio un error al momento de asignar la direccion IP\n");
		exit(1);
	}

	printf("Creando Socket ....\n");
	if( ( sockfd = socket( AF_INET, SOCK_STREAM, 0) ) < 0 )
	{
		perror("Ocurrio un problema en la creacion del socket\n");
		exit(1);
	}

	printf("Estableciendo conexion ...\n");
	if( connect(sockfd, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor) ) < 0) 
	{
		perror ("Ocurrio un problema al establecer la conexion\n");
		exit(1);
	}

	printf("Recibiendo contestacion del servidor ...\n");
	if( read( sockfd, mensaje, TAM_BUFFER ) < 0)
	{	
		perror ("Ocurrio algun problema al recibir datos del cliente\n");
		exit(1);
	}
	
	printf("\nEl servidor envio el siguiente mensaje: \n%s\n\n", mensaje);
	printf("Cerrando la aplicacion cliente\n");

	close( sockfd );

	return 0;
}
