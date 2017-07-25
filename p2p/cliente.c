#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "control.h"
#include "cliente.h"

//sockets
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

extern int port, *nenvios;
extern Conexion envio[10];

/*Recibe la solicitud de "control" y la envía al peer*/
int solLista_CtrlPeer (){
	int i, nlines;
	char output[1000][100];
	
	for(i = 0; i<(*nenvios) ; i++){
		printf("socket = %d\n", envio[i].sock);

		send(envio[i].sock, "consulta", MAXLINE, 0);

		nlines = 0;
		while(1){
			recv(envio[i].sock, &output[nlines], MAXLINE, 0);

			if(strcmp(output[nlines],"end_of_ls") == 0)
			break;

			nlines++;
		}

		//impr_ls(envio[i].nom, output, nlines);
	}
	return 0;
}

/*Solicita la lista de nodos a los que está conectado el otro peer*/
int solNodos_PeerCtrl(int sock, char *machine_names[100]){
	send(sock, "machine_names", MAXLINE, 0);
    int nmachines = 0;
      
	while(1){
		recv( sock, &machine_names[nmachines], MAXLINE, 0);        
		printf("<- %s\n", machine_names[nmachines]);

		if(strcmp(machine_names[nmachines],"end_of_machine_names") == 0) break;
		nmachines++;
	}
	return nmachines;
}

/*Recibe la solicitud de "control" y la envía al peer*/
int solArch_CtrlPeer (){
	return 0;
}


/*Recibe el archivo que envia el peer*/
int recArch_CtrlPeer (){
	return 0;
}


/*Crea cliente
	-Función principal del cliente
*/
int cliente(char ip[]){
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