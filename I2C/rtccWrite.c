/*gcc rtccWrite.c -o rtccWrite -lwiringPi*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wiringPi.h>
#include<wiringPiI2C.h>

#define DIR_RTCC 0x68

int main( void ){
	int iic_fd, i, hora[3] = { 0x39, 0x58, 0x14};
			      // seg   min   hr

	iic_fd = wiringPiI2CSetup( DIR_RTCC );
	if( iic_fd == -1){
		perror("Error al inicializar el bus IIC");
		exit( EXIT_FAILURE );
	}
	
	for( i = 0; i < 3 ; i++ ){
		wiringPiI2CWriteReg8( iic_fd, i, hora[i]);
		usleep( 2000 );
	}

	return 0;
}
