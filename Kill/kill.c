#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<signal.h>

#define NUM_PROC 4

void proceso_padre( pid_t pid[] );
void proceso_hijo( int np );
void manejador();

int main( void ){
	pid_t pid[NUM_PROC];
	register int np;
	
	printf("Probando procesos con señales...\n");
	
	if( signal( SIGUSR1, manejador ) == SIG_ERR ){
		printf("Error en el manejador");
		exit( EXIT_FAILURE );
	}

	for( np = 0 ; np < NUM_PROC ; np++ ){
		pid[np] = fork();
		if( pid[np] == -1 ){
			perror("Eror al crear el proceso...\n");
			exit(EXIT_FAILURE);
		}
		else if( !pid[np]  )
			proceso_hijo( np );
	}
	proceso_padre( pid );

	return 0;
}

void manejador( int sig ){
	if( sig == SIGUSR1 )
		printf("Señal de usuario 1 recibida\n");
}

void proceso_padre( pid_t pid[] ){
	pid_t aux_pid;
	int estado;
	register int np;
	for( np = 0; np < NUM_PROC ; np++ ){
		kill( pid[np], SIGUSR1 );
		sleep(3);
		aux_pid = wait( &estado );
		printf("Proceso hijo %d con retorno: %d\n", aux_pid, estado>>8);
	}
}

void proceso_hijo( int np ){
	printf("Proceso hijo %d ejecutado con pid: %d\n", np, getpid());
	pause();
	printf("Se recibio una señal en el proceso hijo\n");

	exit( np );
}


