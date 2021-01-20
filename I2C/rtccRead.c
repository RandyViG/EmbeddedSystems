/*gcc rtccRead.c -o rtccRead -lwiringPi*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wiringPi.h>
#include<wiringPiI2C.h>

#define DIR_RTCC 0x68

int main( void ){
	int iic_fd, i, hora[3];
	iic_fd = wiringPiI2CSetup( DIR_RTCC );
	
	if( iic_fd == -1){
		perror("Error al inicializar el bus IIC");
		exit( EXIT_FAILURE );
	}

	while(1){
		for( i = 0; i < 3 ; i++){
			hora[i] = wiringPiI2CReadReg8( iic_fd, i);
			usleep( 2000 );
		}	
		printf("\rLa hora es: %x:%x:%x", hora[2],hora[1],hora[0]);
	}
	
	return 0;
}
