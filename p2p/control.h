 /* File control.h */
 #ifndef CONTROL_H
 #define CONTROL_H

#define MAXLINE 100

typedef struct { int sock; char nom[MAXLINE]; } Conexion; /*Estructura donde se guara el identificador del socket y nombre asigando*/
extern int errno;			  /*Variable global donde se capura un posible error*/


int exist_conex(char maquina[]);

int conecta(char ip[]);

int conectarRed ();

int solArch_Inter ();

int solArch_InterCli ();

int terminar_Inter ();


 #endif /* CONTROL_H */