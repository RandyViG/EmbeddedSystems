#ifndef SERVIDOR_H
#define SERVIDOR_H

void atiende_cliente( int cliente_sockfd, int pipefd[] );
void ini_servidor( struct sockaddr_in * direccion_servidor );

#endif