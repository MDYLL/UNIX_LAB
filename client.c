/* Код клиента на языке Си */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define port 5002

char* encrypt(char* message)
{
	char* output=(char*)malloc(200);
	for (int i=0;i<strlen(message);i++)
		output[i]=message[i]+1;
	output[strlen(message)]=0;
	return output;

}

char* decrypt(char* message)
{
	char* output=(char*)malloc(200);
	for (int i=0;i<strlen(message);i++)
		output[i]=message[i]-1;
	output[strlen(message)]=0;
	return output;

}
int main(int argc , char *argv[])
{
	int sock;
	struct sockaddr_in server;
	char message[200] , server_reply[200],sudo_message[200]="sudo ";
	
	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( port );

	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connect failed. Error");
		return 1;
	}
	
	puts("Connected\n");
	
	//keep communicating with server
	while(1)
	{
		printf("Enter message : ");
		fgets(message,200,stdin);
		//strcat(sudo_message,message);
		printf("input message - %s\n", message);
		printf("len - %d\n", (int)strlen(message));
		
		
		//Send some data
		if( send(sock , encrypt(message) , strlen(message) , 0) < 0)
		{
			puts("Send failed");
			return 1;
		}
		
		//Receive a reply from the server
		if( recv(sock , server_reply , 200 , 0) < 0)
		{
			puts("recv failed");
			break;
		}
		server_reply[strlen(server_reply)]=0;
		memset(message,0,200);
		memset(message,0,200);
		strcat(message,"sudo ");
		if (server_reply[0]==0)
			continue;
		printf("%s", decrypt(server_reply));
		memset(server_reply,0,200);
		while ( recv(sock , server_reply , 200 , 0) > 0 && server_reply[0]!=0)
		{
			printf("%s", decrypt(server_reply));
			memset(server_reply,0,200);
		}
	}
	
	close(sock);
	return 0;
}
