/*
 * conexiones.h
 *
 *  Created on: 3 mar. 2019
 *      Author: utnso
 */

#ifndef CONEXIONES_H_
#define CONEXIONES_H_

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/log.h>
#include<commons/collections/list.h>
#include<string.h>
#include<pthread.h>


#define IP "127.0.0.1"
#define PUERTO "4444"

typedef enum
{
	MENSAJE,
	PAQUETE
}op_code;

t_log* logger;

void* recibir_buffer(int*, int);

int iniciar_servidor(t_log* l);
int esperar_cliente(int);
t_list* recibir_paquete(int);
void recibir_mensaje(int);
int recibir_operacion(int);
void* noficar_salida_de_cliente(int estadoHijo);
void* atender_cliente(void* server_fd);
int escucharCliente(t_log* logger, int listenningSocket);

#endif /* CONEXIONES_H_ */
