 /* File control.h */
 #ifndef CONTROL_H
 #define CONTROL_H

#define MAXLINE 100

typedef struct { int sock; char nom[MAXLINE]; } Conexion; /*Estructura donde se guara el identificador del socket y nombre asigando*/

int exist_conex(char maquina[]);

void conecta_cliente(char ip[] );

int conectarRed ();

int solArch_Inter ();

int solArch_InterCli ();

void actNodos_Peer ();

int terminar_Inter ();


 #endif /* CONTROL_H */