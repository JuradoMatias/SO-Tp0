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

	int server_fd = iniciar_servidor();
	log_info(logger, "Servidor listo para recibir al cliente");
	
	pthread_t hilo;
	while(1){
	pthread_create(&hilo,NULL, atender_cliente,(void*) server_fd);
	}

	return EXIT_SUCCESS;
}
