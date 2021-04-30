/*
 * Cliente.h
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#ifndef TP0_H_
#define TP0_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>

#include "utils.h"


t_log* iniciar_logger(void);
t_config* leer_config(void);
void leer_consola(t_log* logger);
void paquete(int);
void terminar_programa(int, t_log*, t_config*);
t_paquete* preparar_paquete();

void leer_consola_haciendo(void(*accion) (char*));

#endif /* TP0_H_ */
