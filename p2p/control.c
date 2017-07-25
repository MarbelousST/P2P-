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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interfaz.h"
#include "control.h"
#include "cliente.h"
#include "servidor.h"

//Memoria compartida
#include <sys/shm.h>

//sockets
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


extern int errno;			  /*Variable global donde se capura un posible error*/
Conexion envio[100];              /*Sockets a los que se les ha enviado petición de conexión*/
int *nenvios, port = 50000;   /*número de envios de peticiones, puerto por el que se conecta el proceso servidor*/


/*Verifica si existe conexión entre una máquina remota y el peer local*/
int exist_conex(char maquina[]){
	int i;

	for(i = 0; i<(*nenvios); i++){
		if(strcmp(maquina, envio[i].nom) == 0) 
	 		return 1;
	}
	return 0;
}

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

	FILE *lnodos = NULL;			/*Archivo donde se guardan los nodos de la red*/
	char ip_nodo[40];		/*Ip del nodo a conectar*/
	int nn = 0, conn = 0, j, k;
	char *machine_name[100];
	int nmachines = 0;

	//Abrimos el archivo de nodos guardados
	lnodos = fopen("lista_nodos.in", "r");
	if (lnodos==NULL) {
		fputs ("File error",stderr); exit (1);
	}


	//lee caca uno de los nodos del archivo y hace una conexión entre el peer y el nodo
	while ( feof( lnodos ) == 0 ){
		fgets( ip_nodo, 40, lnodos );
		printf("Conectando a la Red ...\n");
		if ( !exist_conex( ip_nodo ) && (conn = cliente(ip_nodo)) != -1){

			// Cada vez que se realiza una conexión exitosa se guarda en la lista de envios 
			nn = (*nenvios);

			//Son las conexiones abiertas con otros nodos
			(*nenvios)++;
			printf("%d!!!![[ se conecto ! ]]\n", port);
			envio[ nn ].sock = conn;            	
     		strcpy(envio[nn].nom, ip_nodo);
     		printf("por el socket %d\n", envio [ nn ].sock);

     		// 
		}
		else{
			printf("No se pudo conectar a %s :: %d\n",ip_nodo, port);
		}
	}
	fclose ( lnodos );

	/*Una vez realizada todas las conexiones hace una petición a cada uno de los nodos
	  para que regresen sus listas de nodos
	*/
	for(j = 0; j<(*nenvios); j++){
       nmachines = solNodos_PeerCtrl(envio[ j ].sock, machine_name);

       /*Por cada lista que regresan los nodos se hace una conexión 
       con los que aun no hay una conexión*/
       for (int k = 0; k < nmachines; k++){

    		if(!exist_conex(machine_name[k]) && 
    		(conn = cliente(machine_name[k])) != -1){
    			envio[(*nenvios)].sock = conn;       
        		strcpy(envio[(*nenvios)].nom, machine_name[k]);     
        		(*nenvios)++;
    		}
       }
    }  
    actNodos_Peer();
	printf("Termina la funcion conectarRed\n");
	
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
void actNodos_Peer (){
	FILE *lnodos = NULL;
	int i;
	lnodos = fopen("lista_nodos.in", "w+");
	if (lnodos==NULL) {
		fputs ("File error",stderr); exit (1);
	}

	for (int i = 0; i < (*nenvios); i++){
		fputs(envio[i].nom, lnodos);
	}

	fclose ( lnodos );
	return;
}




/*Solicitud de la interfaz de la lista de archivos que existe en la red.
  	-Hace una petición a cada uno de los nodos de la red 
  	 para que realicen el comando "ls" en la carpeta de 
  	 archivos compartidos*/
	//Consultar los archivos de cada nodo para mostrarlas al cliente
int solArch_Inter (){
	printf("Solicitando lista de archivos a los servidores...\n\n");
	printf("*Número de conexiones : %d\n", (*nenvios));

	return 0;
}


/*Manda la solicitud del archivo desde la interfaz al módulo cliente
*/
int solArch_InterCli (){
	printf("Solicita archivo, función de control\n");
	return 0;
}

/*Guarda el archivo solicitado por el módulo cliente en los archivos compartidos
*/
int GuardArch_Cli (){
	return 0;
}


/*Cierra todas las conexiones*/
int terminar_Inter(){
	printf("Termiando procesos, función de control\n");

	return 0;
	return 0;
}

int main (){

printf("asdgasd\n");
	(nenvios) = 0;

	//conectarRed();
	//aceptConex_Ctrl ();
	interfaz();


	return 0;
}