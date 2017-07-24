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
//#include "cliente.h"
//#include "servidor.h"

//Memoria compartida
#include <sys/shm.h>

//sockets
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

Conexion *envio;              /*Sockets a los que se les ha enviado petición de conexión*/
int *nenvios, port = 50000;   /*número de envios de peticiones, puerto por el que se conecta el proceso servidor*/


/*Verifica si existe conexión entre una máquina remota y el peer*/
int exist_conex(char maquina[]){
	int i;

	for(i = 0; i<(*nenvios); i++){
		if(strcmp(maquina, envio[i].nom) == 0) 
	 		return 1;
	}
	return 0;
}

int conecta(char ip[]) {
	int c, i = 1, id;
	struct sockaddr_in cliente;

	id = socket(PF_INET,SOCK_STREAM,0);                            // creamos un socket 
	if (id == -1){
        printf("Could not create socket");
    }

	setsockopt(id,SOL_SOCKET,0,&i,sizeof(i));
	cliente.sin_family = AF_INET;                                  // familia porque nuestro socket va a ser utilizado sobre una red
	cliente.sin_port = htons(port);                                // puerto de salida
	printf("puerto utilizado : %d\n", port);
	cliente.sin_addr.s_addr = inet_addr(ip);                       //ip del server
	memset(&(cliente.sin_zero), 0, 8); 

	c = connect(id,(struct sockaddr *)&cliente,sizeof(struct sockaddr));
	printf("c ::: %d\n", c);
	return (c == 0) ? id : -1;
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
	int nn = 0, conn = 0;

	lnodos = fopen("lista_nodos.in", "r");
	if (lnodos==NULL) {
		fputs ("File error",stderr); exit (1);
	}

	while ( feof( lnodos ) == 0 ){
		fgets( ip_nodo, 40, lnodos );
		printf("Conectando a la Red ...\n");
		if ( !exist_conex( ip_nodo ) && (conn = conecta(ip_nodo)) != -1){

			nn = (*nenvios);
			(*nenvios)++;
			printf("%d!!!![[ se conecto ! ]]\n", port);
			envio[ nn ].sock = conn;            
     		strcpy(envio[nn].nom, ip_nodo);
     		printf("por el socket %d\n", envio [ nn ].sock);
		}
		else{
			printf("No se pudo conectar a %s :: %d\n",ip_nodo, port);
		}
	}

	printf("Termina la funcion conectarRed\n");
	fclose ( lnodos );
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
	printf("Muestra archivos, función de control\n");
	return 0;
}


/*Manda la solicitud del archivo desde la interfaz al módulo cliente
*/
int solArch_InterCli (){
	printf("Solicita archivo, función de control\n");
	return 0;
}

/*Solicitud de búsqueda desde el módulo servidor
	-Busca el archivo en los archivos compartidos que solicita otro peer desde el módulo servidor
*/
int busArch_Serv (){
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

	int idmem2, idmem;
  	idmem =  shmget(IPC_PRIVATE, sizeof(Conexion)*1000, 0777);
  	idmem2 =  shmget(IPC_PRIVATE, sizeof(int)*1, 0777);
  
  	if ( idmem == -1 ){
  		printf("No se pudo crear Memoria Compartida. \n");
  	}

  	else{
  		envio = (Conexion *)shmat(idmem, (char *)0, 0);    
  		nenvios = (int *)shmat(idmem2, (char *)0, 0); 

  		if (shmdt( (char *)envio ) < 0 ){
  			printf(" Error : shmdt. \n");
  		}

  		//conectarRed();
  		interfaz();
	  	shmctl(idmem, IPC_RMID, (struct shmid_ds *)NULL );
	  	shmctl(idmem2, IPC_RMID, (struct shmid_ds *)NULL );
  	}


	return 0;
}