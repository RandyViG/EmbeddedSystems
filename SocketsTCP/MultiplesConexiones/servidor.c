#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define PUERTO 5000
#define COLA_CLIENTES 5
#define TAM_BUFFER 100

int main(int argc, char **argv){
	int sockfd, cliente_sockfd;
	struct sockaddr_in direccion_servidor;
	char leer_mensaje[TAM_BUFFER];
	pid_t pid;
	
	memset( &direccion_servidor, 0, sizeof(direccion_servidor) );
	direccion_servidor.sin_family = AF_INET;
	direccion_servidor.sin_port = htons(PUERTO);
	direccion_servidor.sin_addr.s_addr = INADDR_ANY;

	printf("Creando Socket ....\n");
	if( ( sockfd = socket(AF_INET, SOCK_STREAM, 0) ) < 0 ){
		perror("Ocurrio un problema en la creacion del socket\n");
		exit( EXIT_FAILURE );
	}

	printf("Configurando socket ...\n");
	if( bind( sockfd, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor) ) < 0 ){
		perror ("Ocurrio un problema al configurar el socket\n");
		exit(1EXIT_FAILURE );
	}
	
	printf("Estableciendo la aceptacion de clientes...\n");
	if( listen(sockfd, COLA_CLIENTES) < 0 ){
		perror("Ocurrio un problema al crear la cola de aceptar peticiones de los clientes\n");
		exit( EXIT_FAILURE );
	}

	while( 1 ){
		printf("En espera de peticiones de conexión ...\n");
		if( ( cliente_sockfd = accept(sockfd, NULL, NULL) ) < 0 ){
			perror("Ocurrio algun problema al atender a un cliente");
			exit( EXIT_FAILURE );
		}
		pid = fork();
		if( !pid ){
			printf("Se aceptó un cliente, atendiendolo \n");
			if( read(cliente_sockfd, leer_mensaje, TAM_BUFFER) < 0 ){
				perror ("Ocurrio algun problema al recibir datos del cliente");
				exit( EXIT_FAILURE );
			}
			printf("El cliente nos envio el siguiente mensaje: \n %s \n", leer_mensaje);
			if( write(cliente_sockfd, "Bienvenido cliente", 19) < 0 ){
				perror("Ocurrio un problema en el envio de un mensaje al cliente");
				exit( EXIT_FAILURE );
			}	

			close( cliente_sockfd );
			exit( 0 );
		}
	}
	printf("Concluimos la ejecución de la aplicacion Servidor \n");
	close( sockfd );

	return 0;
}
