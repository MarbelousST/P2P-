#include <stdio.h>
#include <stdlib.h>
#include "control.h"
#include "interfaz.h"

/*Solicita una consulta a "control"
	-control realizará una petición de todos los archivos en la red
	e imprime resultado
*/
void consulta_Ctrl (){
	system("clear");
	printf("Consultado los archivos en la red...\n");
	solArch_Inter ();
	return;
}

/*Selecciona de la lista de archivos
	-Realiza una solicitud del archivo a "control" para que la procese
*/
void selecArch_Ctrl (){
	system("clear");
	printf("Descargando archivo\n");
	solArch_InterCli ();

	return;
}

/*Realiza solicitud de finalización de procesos a "control"*/
void salir_Ctrl (){
	system("clear");
	printf("Saliendo de la aplicación\n");
	terminar_Inter();	
	return;
}


/*Despliega las opciones de la aplicación al usaurio
	-Función principal de la interfaz
*/
void interfaz(){

	int opc = 0;



	do{ 	
	 	printf("Interfaz de usuario ...\n\n\n");
		printf("Selecciona una opción de la sigueinte lista:\n");
		printf("1) Consulta los archivos de la red\n");
		printf("2) Selecciona archivo\n");
		printf("3) Salir\n");
		printf(">>: ");
	   	scanf("%d", &opc);
	    printf("[%c]\n", opc);
	    printf("comando : %d\n", opc);
	    if(opc == 1){ 
	    	consulta_Ctrl();
	    }
	    else if (opc == 2){
	    	selecArch_Ctrl();
	    }
	    else if(opc == 3){
	    	salir_Ctrl();
	    }
	    else{
	    	system("clear");
	    	printf("%d No es una opción válida.\n", opc);
	    } 
	                  
	}
	while(opc != 10);   
	     
	return;
}