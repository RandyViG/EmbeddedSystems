#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"defs.h"

void obtener_datos( char *buffer, char * mensaje ){
	int register i = 0;
	char time[10], latitude[11], longitude[12], n_s=42, e_w=42, *ptr;
	memset( time, 0, 10);
	memset( latitude, 0, 11);
	memset( longitude, 0, 12);
	memset( time, 42, 3);
	memset( latitude, 42, 3);
	memset( longitude, 42, 3);
	if( strlen(buffer) == 76 )
		sscanf(buffer, "%*7s%9s%*1s%10s%*1s%c%*1s%11s%*1s%c", time, latitude, &n_s,longitude, &e_w);
	else{
		ptr = buffer + 6; 
		for( i = 0 ; i < 5 ; i++ ){
			if( i == 0 ){
				if( *(ptr+1) != 44 ){
					memcpy( time, ptr + 1 , 9 );
					ptr += 9;
				}
			}else if( i == 1 ){
				if( *(ptr+1) != 44 ){
					memcpy( latitude, ptr + 1, 10 );
					ptr += 10;
				}
			}else if( i == 2 ) {
				if( *(ptr+1) != 44 ){
					memcpy( &n_s, ptr + 1 , 1 );
					ptr += 1;
				}
			}else if( i == 3 ){
				if( *(ptr+1) != 44 ){
					memcpy( longitude, ptr + 1 , 11 );
					ptr += 11;
				}
			}else if( i == 4 ){
				if( *(ptr+1) != 44 )
					memcpy( &e_w, ptr + 1, 1 );
			}
			ptr += 1;
		}
	}

	sprintf(mensaje,"time:%s latitude:%s N/S:%c longitude:%s E/W:%c",time, latitude, n_s, longitude, e_w);
}
