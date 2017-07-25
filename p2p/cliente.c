#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "control.h"
#include "cliente.h"


/*Recibe la solicitud de "control" y la envía al peer*/
int solLista_CtrlPeer (){
	int i, nlines;
	char output[1000][100];
	
	for(i = 0; i<(*nenvios) ; i++){
		printf("socket = %d\n", envio[i].sock);

		send(envio[i].sock, "make_ls", MAXLINE, 0);

		nlines = 0;
		while(1){
			recv(envio[i].sock, &output[nlines], MAXLINE, 0);

			if(strcmp(output[nlines],"end_of_ls") == 0)
			break;

			nlines++;
		}

		impr_ls(envio[i].nom, output, nlines);
	}
	return 0;
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
int cliente(){
	return 0;
}