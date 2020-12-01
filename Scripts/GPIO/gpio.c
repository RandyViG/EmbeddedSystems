/* @brief:
 * Este programa configura el BCM_GPIO 16 usando la libreria wiringPi
 * El GPIO 16 corresonde con el pin 27 en wiring Pi
 * compilar: gcc gpio.c -o gpio -lwiringPi 
 * */

#include<stdio.h>
#include<unistd.h>
#include<wiringPi.h>

#define PIN 27

int main( void ){
	// Inizializa la libreria wiring Pi
	wiringPiSetup();
	// Se configura el GPIO 16 como salida
	pinMode( PIN, OUTPUT );

	// Se escribe un valor digital al GPIO
	while( 1 ){
		digitalWrite( PIN, HIGH );
		sleep( 1 );
		digitalWrite( PIN, LOW );
		sleep( 1 );
	}
       return 0;	
}
