/*
 * main.c
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#include "tp0.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;
	char* CLAVE_valor;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();

	//Loggear "soy un log"
	//char* mensaje_a_enviar = "soy un log";
	//log_info(logger,mensaje_a_enviar);

	config = leer_config();
	CLAVE_valor = config_get_string_value(config,"CLAVE");
	log_info(logger,CLAVE_valor); //se inserta el valor de la CLAVE del archivo config

	//asignar valor de config a la variable valor

	//Loggear valor de config

	//leer_consola(logger);


	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	//antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	//crear conexion
	ip = config_get_string_value(config,"IP");
	puerto = config_get_string_value(config,"PUERTO");
	conexion = crear_conexion(ip,puerto);

	//enviar CLAVE al servidor
	//enviar_mensaje(CLAVE_valor,conexion);
	
	t_paquete* paquete = preparar_paquete();
	enviar_paquete(paquete,conexion);  

	eliminar_paquete(paquete);
	terminar_programa(conexion, logger, config);
}

t_log* iniciar_logger(void)
{
	return log_create("tp0.log","tp0",1,LOG_LEVEL_INFO);
}

t_config* leer_config(void)
{
	return config_create("tp0.config");
}

void leer_consola(t_log* logger)
{
	void loggear(char* leido)
	{
		log_info(logger,leido);
	}

	leer_consola_haciendo((void*) loggear);
}

void leer_consola_backup(t_log* logger)
{
	char* leido;

	//El primero te lo dejo de yapa
	leido = readline(">");
	
	while(strncmp(leido,"",1) != 0)
	{
		log_info(logger,leido);
		free(leido); 
		leido = readline(">");
	}

}

void leer_consola_haciendo(void(*accion)(char*))
{
	char* leido;

	//El primero te lo dejo de yapa
	leido = readline(">");
	
	while(strncmp(leido,"",1) != 0)
	{
		accion(leido);
		free(leido);
		leido = readline(">");
	}

	free(leido); 
}

t_paquete* preparar_paquete(){

	t_paquete* paquete = crear_paquete();

	void agregar(char* leido){
		agregar_a_paquete(paquete,leido,strlen(leido)+1);
	}

	leer_consola_haciendo((void*) agregar);

	return paquete;
}

void leer_consola_agregar_a_paquete(t_log* logger)
{
	char* leido;

	//El primero te lo dejo de yapa
	leido = readline(">");
	
	while(strncmp(leido,"",1) != 0)
	{
		log_info(logger,leido);
		free(leido); 
		leido = readline(">");
	}

}

void paquete(int conexion)
{
	//Ahora toca lo divertido!

	char* leido;
	//char* todas_las_lineas;
	t_paquete* paquete;
	paquete = crear_paquete();

	leido = readline(">");

		while(strncmp(leido,"",1) != 0)
	{
		//strncat(todas_las_lineas,leido,strlen(leido));
		agregar_a_paquete(paquete,leido,strlen(leido)+1);
		leido = readline(">");
	}

	free(leido); 


	//free(todas_las_lineas);

	enviar_paquete(paquete,conexion);
	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
	log_destroy(logger);
	liberar_conexion(conexion);
	config_destroy(config);
}
