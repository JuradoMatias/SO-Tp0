/*
 * servidor.c
 *
 *  Created on: 3 mar. 2019
 *      Author: utnso
 */

#include "servidor.h"

int main(void)
{
	// void iterator(char* value)
	// {
	// 	printf("%s\n", value);
	// }

	logger = log_create("log.log", "Servidor", 1, LOG_LEVEL_DEBUG);

	log_info(logger, "Point1");

	int socket_escucha = iniciar_servidor(logger);
	log_info(logger, "Servidor listo para recibir al cliente");


	while (1) { // Infinitamente escucha a la espera de que se conecte alguien
		int socketCliente = escucharCliente(logger, socket_escucha);
		pthread_t unHilo; // Cada conexion la delega en un hilo
		pthread_create(&unHilo, NULL, (void*) atender_cliente, (void*) &socketCliente);
	}

	return EXIT_SUCCESS;
}
