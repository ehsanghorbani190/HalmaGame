#include "socket.c"

SOCKET InititClient(char *host,int port);
SOCKET InitServer(int port);
int Recieve(int s, char *buf, int maxLen);
int Send(SOCKET s,char *data);
struct Client WaitForClient(SOCKET s);
