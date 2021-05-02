/*
 * conexiones.c
 *
 *  Created on: 3 mar. 2019
 *      Author: utnso
 */

#include"utils.h"

int iniciar_servidor(t_log* log)
{

	/*
	 *  ¿Quien soy? ¿Donde estoy? ¿Existo?
	 *
	 *  Estas y otras preguntas existenciales son resueltas getaddrinfo();
	 *
	 *  Obtiene los datos de la direccion de red y lo guarda en serverInfo.
	 *#include "misHilos.c"
	 */


	struct addrinfo hints;
	struct addrinfo *serverInfo;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;		// No importa si uso IPv4 o IPv6
	hints.ai_flags = AI_PASSIVE;		// Asigna el address que le envia el proceso
	hints.ai_socktype = SOCK_STREAM;	// Indica que usaremos el protocolo TCP

	

	getaddrinfo(IP, PUERTO, &hints, &serverInfo);



	/*
	 * 	Descubiertos los misterios de la vida (por lo menos, para la conexion de red actual), necesito enterarme de alguna forma
	 * 	cuales son las conexiones que quieren establecer conmigo.
	 *
	 * 	Para ello, y basandome en el postulado de lo que se usa siempre en Linux, voy a utilizar... Si, un archivo!
	 *
	 * 	Mediante socket(), obtengo el File Descriptor que me proporciona el sistema (un integer identificador).
	 *
	 */
	/* Necesitamos un socket que escuche las conecciones entrantes */


	int socket_servidor;
	socket_servidor = socket(serverInfo->ai_family, serverInfo->ai_socktype,serverInfo->ai_protocol);

		// Si habia quedado algun bit de conexion lo limpio
	int yes=1;
	// lose the pesky "Address already in use" error message
	if ((setsockopt(socket_servidor, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)){
	    perror("Error");
	    exit(1);
	}
	

    // 	/*
	//  * 	Perfecto, ya tengo un archivo que puedo utilizar para analizar las conexiones entrantes. Pero... ¿Por donde?
	//  *
	//  * 	Necesito decirle al sistema que voy a utilizar el archivo que me proporciono para escuchar las conexiones por un puerto especifico.
	//  *
	//  * 				OJO! Todavia no estoy escuchando las conexiones entrantes!
	//  *
	//  */
	
	if (bind(socket_servidor, serverInfo->ai_addr, serverInfo->ai_addrlen) < 0) perror("Error");
	freeaddrinfo(serverInfo); // Ya no lo vamos a necesitar
	

	/*
	 * 	Descubiertos los misterios de la vida (por lo menos, para la conexion de red actual), necesito enterarme de alguna forma
	 * 	cuales son las conexiones que quieren establecer conmigo.
	 *
	 * 	Para ello, y basandome en el postulado de lo que se usa siempre en Linux, voy a utilizar... Si, un archivo!
	 *
	 * 	Mediante socket(), obtengo el File Descriptor que me proporciona el sistema (un integer identificador).
	 *
	 */
	/* Necesitamos un socket que escuche las conecciones entrantes */
	listen(socket_servidor, SOMAXCONN);

	log_info(log,"Point2");
    //log_trace(logger, "Listo para escuchar a mi cliente");

    return socket_servidor;
}

int esperar_cliente(int socket_servidor)
{
	struct sockaddr_in dir_cliente;
	int tam_direccion = sizeof(struct sockaddr_in);

	int socket_cliente = accept(socket_servidor, (void*) &dir_cliente, &tam_direccion);

/* 
		while(fork() != -1)
	{
		// case -1:
		// // el fork no me creo nada
		// printf("se rompio todo");
		// break;
		if(fork() == 0)
		{
		// codigo del hijo
		log_info(logger, "Se conecto un cliente!");
		return socket_cliente;

		}else
		{
		// codigo del padre - original
		pthread_t id_hilo;
		pthread_create(&id_hilo,NULL,noficar_salida_de_cliente,NULL);
		pthread_Exit();
		int socket_cliente = accept(socket_servidor, (void*) &dir_cliente, &tam_direccion);

		}
	}
	*/
			
log_info(logger, "Se conecto un cliente!");
return socket_cliente;
}

int escucharCliente(t_log* logger, int listenningSocket) {
	//log_info(logger, "Listo para escuchar a cualquier Cliente...");
	//listen(listenningSocket, SOMAXCONN); // IMPORTANTE: listen() es una syscall BLOQUEANTE.

	/*
	 * 	El sistema esperara hasta que reciba una conexion entrante...
	 * 	...
	 * 	...
	 * 	BING!!! Nos estan llamando! ¿Y ahora?
	 *
	 *	Aceptamos la conexion entrante, y creamos un nuevo socket mediante el cual nos podamos comunicar (que no es mas que un archivo).
	 *
	 *	¿Por que crear un nuevo socket? Porque el anterior lo necesitamos para escuchar las conexiones entrantes. De la misma forma que
	 *	uno no puede estar hablando por telefono a la vez que esta esperando que lo llamen, un socket no se puede encargar de escuchar
	 *	las conexiones entrantes y ademas comunicarse con un cliente.
	 *
	 *			Nota: Para que el listenningSocket vuelva a esperar conexiones, necesitariamos volver a decirle que escuche, con listen();
	 *				En este ejemplo nos dedicamos unicamente a trabajar con el cliente y no escuchamos mas conexiones.
	 *
	 */
	struct sockaddr_in addr; // Esta estructura contendra los datos de la conexion del cliente. IP, puerto, etc.
	socklen_t addrlen = sizeof(addr);

	int socketCliente = accept(listenningSocket, (struct sockaddr *) &addr,	&addrlen);

	return socketCliente;
}

int recibir_operacion(int socket_cliente)
{
	int cod_op;
	if(recv(socket_cliente, &cod_op, sizeof(int), MSG_WAITALL) != 0)
		return cod_op;
	else
	{
		close(socket_cliente);
		return -1;
	}
}

void* recibir_buffer(int* size, int socket_cliente)
{
	void * buffer;

	recv(socket_cliente, size, sizeof(int), MSG_WAITALL);
	buffer = malloc(*size);
	recv(socket_cliente, buffer, *size, MSG_WAITALL);

	return buffer;
}

void recibir_mensaje(int socket_cliente)
{
	int size;
	char* buffer = recibir_buffer(&size, socket_cliente);
	log_info(logger, "Me llego el mensaje %s", buffer);
	free(buffer);
}

//podemos usar la lista de valores para poder hablar del for y de como recorrer la lista
t_list* recibir_paquete(int socket_cliente)
{
	int size;
	int desplazamiento = 0;
	void * buffer;
	t_list* valores = list_create();
	int tamanio;

	buffer = recibir_buffer(&size, socket_cliente);
	while(desplazamiento < size)
	{
		memcpy(&tamanio, buffer + desplazamiento, sizeof(int));
		desplazamiento+=sizeof(int);
		char* valor = malloc(tamanio);
		memcpy(valor, buffer+desplazamiento, tamanio);
		desplazamiento+=tamanio;
		list_add(valores, valor);
	}
	free(buffer);
	return valores;
	return NULL;
}


void* noficar_salida_de_cliente(int estadoHijo)
{
	wait(&estadoHijo);
	if( WIFEXITED(estadoHijo) != 0)
	{
		printf("Mi hijo ha hecho exit (%d)\n", WEXITSTATUS(estadoHijo));
	}
}

void* atender_cliente(void* cliente_fd){
	t_list* lista;

		void iterator(char* value){
		printf("%s\n", value);
	};

	//int server_fd = (void*) server;
	//while(1)
	//{
	//	int cliente_fd = esperar_cliente((int) server_fd);
		int cod_op = recibir_operacion((int) cliente_fd);
		switch(cod_op)
		{
		case MENSAJE:
			recibir_mensaje(cliente_fd);
			break;
		case PAQUETE:
			lista = recibir_paquete(cliente_fd);
			printf("Me llegaron los siguientes valores:\n");
			list_iterate(lista, (void*) iterator);
			break;
		case -1:
			log_error(logger, "el cliente se desconecto. Terminando servidor");
			return EXIT_FAILURE;
		default:
			log_warning(logger, "Operacion desconocida. No quieras meter la pata");
			break;
	//	}
	}

	return 0;

	}