#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/wait.h>
#include<sys/types.h>

#define PUERTO 5000
#define COLA_CLIENTES 5
#define TAM_BUFFER 100
#define EVER 1

int sockfd;
struct sockaddr_in direccion_servidor;

void manjeador( int sig );
void atiende_cliente( int cliente_sockfd );
void ini_servidor( void );
void ini_signals( void );

int main(int argc, char **argv){
	int cliente_sockfd;
	pid_t pid;
	
	ini_signals();
	ini_servidor();

	for( ; EVER ;  ){
		printf("En espera de peticiones de conexión ...\n");
		if( ( cliente_sockfd = accept(sockfd, NULL, NULL) ) < 0 ){
			perror("Ocurrio algun problema al atender a un cliente");
			exit( EXIT_FAILURE );
		}
		pid = fork();
		if( !pid )
			atiende_cliente( cliente_sockfd );
	}

	return 0;
}

void ini_signals( void ){
	if( signal( SIGCHLD, manjeador ) == SIG_ERR ){
		perror("Error en el manejador");
		exit( EXIT_FAILURE );
	}
	if( signal( SIGINT, manjeador ) == SIG_ERR ){
		perror("Error en el manejador");
		exit( EXIT_FAILURE );
	}
}

void ini_servidor( void ){
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
		exit(EXIT_FAILURE );
	}
	printf("Estableciendo la aceptacion de clientes...\n");
	if( listen(sockfd, COLA_CLIENTES) < 0 ){
		perror("Ocurrio un problema al crear la cola de aceptar peticiones de los clientes\n");
		exit( EXIT_FAILURE );
	}
}

void atiende_cliente( int cliente_sockfd ){
	char leer_mensaje[TAM_BUFFER];

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

void manjeador( int sig ){
	int estado;
	pid_t pid;

	if( sig == SIGCHLD ){
		printf("Se recibio la señal SIGCHLD en el servidor\n");
		pid = wait(&estado);
		printf("Termino el proceso: %d con estado: %d\n", pid, estado>>8);
	}
	else if( sig == SIGINT ){
		printf("Se recibio la señal SIGINT en el servidor\n");
		printf("Concluimos la ejecución de la aplicacion Servidor \n");
		close( sockfd );
		exit( 0 );
	}
}

