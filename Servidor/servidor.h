/*
 * servidor.h
 *
 *  Created on: 3 mar. 2019
 *      Author: utnso
 */

#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<commons/log.h>
#include "utils.h"
#include "../shared/include/miAccesoConfiguracion.h"
#include "../shared/include/miSerializador.h"
#include "../shared/include/misSockets.h"



// void establecerConexion(void* socketCliente) {
// 	log_info(logger, "Cliente conectado");

// 	/* Aca se utiliza el concepto de handshake.
// 	 * Cada Cliente manda un identificador para avisarle al Servidor
// 	 * quien es el que se conecta. Esto hay que hacerlo ya que nuestro
// 	 * Servidor es multicliente, y a cada cliente lo atiende con un
// 	 * hilo distinto => para saber cada hilo que ejecutar tiene que
// 	 * saber con quien se esta comunicando =)
// 	 */

// 	uint32_t handshake;
// 	recv(*(int*) socketCliente, &handshake, sizeof(uint32_t), 0);
// 	if (handshake == ESI) {
// 		log_info(logger, "El cliente es ESI");
// 		atenderESI(*(int*) socketCliente);
// 	} else if (handshake == INSTANCIA) {
// 		log_info(logger, "El cliente es una Instancia");
// 		atenderInstancia(*(int*) socketCliente);
// 	} else if (handshake == PLANIFICADOR) {
// 		log_info(logger, "El cliente es el Planificador");
// 		socketPlanificador = *(int*) socketCliente;
// 		send(socketPlanificador, &PAQUETE_OK, sizeof(uint32_t), 0);

// 		// Me conecto como cliente al Planificador para las peticiones de consola
// 		pthread_t hiloConsola;
// 		pthread_create(&hiloConsola, NULL, (void*) atenderConsola, NULL);
// 	} else {
// 		log_error(logger, "No se pudo reconocer al cliente");
// 	}
// }

#endif /* SERVIDOR_H_ */
