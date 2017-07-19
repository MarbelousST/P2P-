/*
*	Creado por:
*	Angeles
*	Erika
*	Fermando
*	Mario Abel Salvador Torres
*
*****************************************************
*
*Aplicación peer to peer.
*
*	Las funciones con el siguiente formato funcionan como 
*	interfaces entre los módulos: control, cliente, servidor e interfaz
*	
*	NombreAccion_Modulo();
*
*	El nombre de cada función se compone de dos partes:
*		-Nombre de la acción que realizará el sistema
*		-Nombre del módulo con el que interactua
*
* 	Las funciones adicionales para el sistema deben seguir el siguiente formato:
*
*	NombreDeLaFuncion();
*	
*		-No se incluye "_" ni el nombre del módulo
*
*	Las funciones que regresan el valor 0 cuando todo funcionó bien
*	Regresan -1 en caso de error
*/

#include <stdio>
#include <stdlib>
#include <string.h>
#include "interfaz.h"
#include "cliente.h"
#include "servidor.h"

/*Realiza una conexión "todos contra todos"

	*** Primera ejecución ***
	-El sistema guarda la referencia del nodo base en un archivo
	-El sistema lee el archivo y se conecta al nodo base
	-Una vez conectado hace una actualización del archivo lista_nodos
	 con la infomación del nodo base

	*** Ejecuciones posteriores
	-El sistema actualiza lista_nodos con la infromación de los demás nodos
	 guardado el registro de todos los nodos de la red

*/
int conectarRed (){

	return 0;
}


/*Envia como respuesta la lista de archivos locales
	-Realiza el comando "ls" en la carpeta de archivos compartidos
*/
int resArch_Peer (){
	return 0;
}


/*Actualiza el archivo lista_nodos con los nodos recividos de la red
	-Se ejecuta una vez hecha la conexión con los demas nodos
*/
int actNodos_Peer (){
	return 0;
}


/*Envia la lista de nodos al peer que lo solicite*/
int envNodos_Peer (){
	return 0;
}


/*Solicitud de la interfaz de la lista de archivos que existe en la red.
  	-Hace una petición a cada uno de los nodos de la red 
  	 para que realicen el comando "ls" en la carpeta de 
  	 archivos compartidos*/
int solArch_Inter (){
	return 0;
}


/*Regresa la lista de archivos obtenidos a la interfaz de usuario
	-Una vez recibido el nombre de los archivos los manda ala interfaz 
	de usario para que sean mostrados en consola 

*/
int reLista_Inter (){
	return 0;
}

/*
*/


/*Cierra todas las conexiones*/
int terminar (){

	return 0;
}

int main (){

	return 0;
}