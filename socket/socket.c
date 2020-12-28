#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "Ws2_32.lib")

 struct Client{
	SOCKET socket;
	char name[50];
	char ip[50];
};
int Recieve(int s, char *buf, int maxLen)
{
    int total = 0;        // how many bytes we've received
    int bytesleft = maxLen; // how many we have left to receive
    int n = -1;

    while(total < maxLen) {
        n = recv(s, buf+total, bytesleft, 0);
		if(*(buf+total)==13)
		break;

        if (n <= 0) { break; }
        total += n;
        bytesleft -= n;
		
    }
	int idxToDel = strlen(buf)-1; 
	memmove(&buf[idxToDel], &buf[idxToDel + 1], strlen(buf) - idxToDel);

    return (n<=0)?1:0; // return -1 on failure, 0 on success
} 
int Send(SOCKET s,char *data){
	data = strcat(data,"\n");
	if( send(s ,  data ,strlen(data), 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
	puts("Data Send\n");
}
SOCKET InititClient(char *host,int port){
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;
	

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}
	
	printf("Initialised.\n");
	
	//Create a socket
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}

	printf("Socket created.\n");
	
	
	server.sin_addr.s_addr = inet_addr(host);
	server.sin_family = AF_INET;
	server.sin_port = htons( 8888 );

	//Connect to remote server
	if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}
	
	puts("Connected");

	return s;
}
SOCKET InitServer(int port)
{
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return 1;
	}

	printf("Initialised.\n");

	//Create a socket
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}

	printf("Socket created.\n");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);

	//Bind
	if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
	}

	puts("Bind done");

	listen(s, 3);

	return s;
}
struct Client WaitForClient(SOCKET s)
{
	int c;
	SOCKET new_socket;
	char *message;
	struct sockaddr_in  clientAdd;
	struct Client client;

	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	if ((new_socket = accept(s, (struct sockaddr *)&clientAdd, &c)) != INVALID_SOCKET)
	{
		puts("Connection accepted");

		//Reply to the client
		message = "Hello Client , I have received your connection. And now I will assign a handler for you\n";
		send(new_socket, message, strlen(message), 0);
		
		Recieve(new_socket,client.name,200);
	
	}
	strcpy(client.ip,inet_ntoa(clientAdd.sin_addr));
	client.socket=new_socket;
	return client;
}




