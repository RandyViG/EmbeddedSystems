#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<syslog.h>
#include<unistd.h>
#include<pthread.h>
#include<wiringPiI2C.h>
#include"defs.h"

extern int leer, escribir;

void * leer_rtcc( void * arg ){
	int *pipefd = (int*)arg;
	int hora[ N ], iic_fd;
	register int i;
	
	iic_fd = wiringPiI2CSetup( DIR_RTCC );

	if( iic_fd == -1 ){
		syslog( LOG_ERR, "Error al iniciar el bus IIC");
		exit( EXIT_FAILURE );
	}

	while( leer ){
		for( i = 0; i < N ; i++ ){
			hora[i] = wiringPiI2CReadReg8( iic_fd, i );
			usleep( 2000 );
		}
		if( escribir )
			write( pipefd[1], hora, sizeof(int) * N );
	}

	close( pipefd[1] );
	syslog( LOG_INFO , "Terminando la ejecución del hilo\n ");
	pthread_exit( (void*) 0 );
}
