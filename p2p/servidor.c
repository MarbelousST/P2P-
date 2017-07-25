#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "control.h"
#include "servidor.h"

//sockets
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//fork
#include  <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern int port, *nenvios;
extern Conexion envio[10];

/*Manda una petición de busqueda al módulo "Control"
	-Recibe la solicitud del cliente de otro peer
*/
int busArch_Ctrl (){
	return 0;
}


/*Envia el archivo solicitado por el cliente
	-Una vez encontrado el archivo en el repositorio local
	 lo envia al cliente que lo solicitó.
*/
int envArch_Peer (){
	return 0;
}
//funcion que envia lista de nodos
int envNodos_Peer(int sock){
	int i;
	//nenvios_numero de envios
  	for(i = 0; i<(*nenvios); i++){
  		if(sock != envio[i].sock){
   			send(sock, envio[i].nom, MAXLINE, 0);
  		}
	}
   //para terminar las conexiones
 	send(sock, "end_of_machine_names", MAXLINE, 0);
	return 0;
}


/*Crea servidor con los hilos para atender a los clientes
	-funciíon principal del servidor*/
int aceptConex_Ctrl (){

	int descriptor_socket, i = 1, desc_arch, pid ;
	struct sockaddr_in 	struct_servidor;
	socklen_t 		tamano_direccion;
	char peticion[MAXLINE], nombre[25], s_puerto[10];

	printf("Aceptando conexiones ...\n\n");
	 /*
	 Inicialización de Socket ...
	 */

 	descriptor_socket = socket(PF_INET, SOCK_STREAM, 0);
 	memset(&struct_servidor, 0, sizeof(struct_servidor)); 
 	struct_servidor.sin_addr.s_addr = htonl(INADDR_ANY);
 	struct_servidor.sin_family = AF_INET;
 	struct_servidor.sin_port = htons( port );
  	tamano_direccion = sizeof ( struct_servidor);
 	bind (descriptor_socket, (struct sockaddr *)&struct_servidor, tamano_direccion);

 	listen( descriptor_socket, 5);
 	printf("Servidor activo con IP = %s, PUERTO = %d\n", inet_ntoa(struct_servidor.sin_addr), ntohs(struct_servidor.sin_port));

   /* ... Acepta las Conexiones ... */
    while ( (desc_arch = accept(descriptor_socket,(struct sockaddr *)&struct_servidor, &tamano_direccion)) >= 0 ){
    	
    	pid = fork( );//por cada conexion se genera un hilo
    	printf("%d\n", pid);
      	if ( pid == 0 ){
      		inet_ntoa(struct_servidor.sin_addr);
        	puts("conexion habilitada");
        //copiamos la direccion del servidor
        	strcpy(nombre, inet_ntoa(struct_servidor.sin_addr));                
        	printf("IP = %s, PORT = %d\n", nombre, ntohs(struct_servidor.sin_port));                
	        /*
	         Recibe el puerto del proceso servidor, del programa que se está conectando a él.
	      
	       */  
             
        	//conecta_cliente(nombre);        
         	//espera las peticiones de los clientes
	        while(1){  
	        	recv(desc_arch, peticion, MAXLINE, 0);
	         	printf(":: %s\n", peticion);
	        	if(strcmp(peticion, "consulta") == 0){
	        		printf("Haciendo consulta de archivos... \n");
	           		//server_side_make_ls(desc_arch);
	        	}
	           
	          	else if(strcmp(peticion, "lista_nodos") == 0){
	           		printf("Enviando lista de nodos ... \n");
	           		envNodos_Peer(desc_arch);
	           		//server_side_send_machine_names(desc_arch);     
	          	}                	 
	          	else if(strcmp(peticion, "seleccionar")==0){
	          		printf("Enviando archivos\n");
	          		envArch_Peer();
	          	}
	          	else if(strcmp(peticion, "quit") == 0){
	            	shutdown(desc_arch, 2);
	            	exit(0);            
	         	}
	          	printf(":: %s ha terminado\n", peticion);
	        }
      	}
    }
	return 0;
}