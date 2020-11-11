#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"archivos.h"

void obtener_datos( char * mensaje ){
	char time[10], latitude[11], longitude[12], n_s, e_w, aux[100];
	leer_archivo( aux, "nmea.txt" );
	sscanf(aux, "%*7s%9s%*1s%10s%*1s%c%*1s%11s%*1s%c", time, latitude, &n_s,longitude, &e_w);
	sprintf(mensaje,"time:%s latitude:%s N/S:%c longitude:%s E/W:%c",time, latitude, n_s, longitude, e_w);
}

void datos( char * mensaje ){
	int register i;
	char time[10], latitude[11], longitude[12], n_s, e_w, aux[100], *ptr;
	leer_archivo( aux, "nmea.txt" );
	ptr = strtok( aux, ",");
	for( i = 0 ; i < 5 ; i++ ){
		ptr = strtok( NULL, ",");
		if( i == 0 )
			memcpy( time, ptr, 10 );
		else if( i == 1 )
			memcpy( latitude, ptr, 11 );
		else if( i == 2 )
			memcpy( &n_s, ptr, 1 );
		else if( i == 3 )
			memcpy( longitude, ptr, 12 );
		else
			memcpy( &e_w, ptr, 1 );
	}
	sprintf(mensaje,"time:%s latitude:%s N/S:%c longitude:%s E/W:%c",time, latitude, n_s, longitude, e_w);
}