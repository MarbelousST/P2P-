 /* File cliente.h */
 #ifndef CLIENTE_H
 #define CLIENTE_H
 
int solLista_CtrlPeer ();
int solNodos_PeerCtrl(int sock, char *machine_names[100]);
int cliente(char ip[]);
 
 #endif /* CLIENTE_H */