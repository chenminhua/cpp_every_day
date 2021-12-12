// server
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in server;
	int mysock; // hold the connection
	char buff[1024];
	int rval; // return value

	sockfd = socket(AF_INET, SOCK_STREAM, 0); // tcp socket
	if (sockfd < 0)
	{
		perror("failed to create socket");
		exit(1);
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(5000);

	/*call bind*/
	if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)))
	{
		perror("bind failed");
		exit(1);
	}

	/*listen*/
	listen(sockfd, 5);

	/*accept*/
	do
	{
		mysock = accept(sockfd, (struct sockaddr *)0, 0);
		if (mysock == -1)
		{
			perror("accept failed");
		}
		else
		{
			memset(buff, 0, sizeof(buff));
			if ((rval = recv(mysock, buff, sizeof(buff), 0)) < 0)
				perror("reading stream message error");
			else if (rval == 0)
				printf("ending connection\n");
			else
				printf("msg: %s\n", buff);
			printf("got the message (rval = %d)\n", rval);
			close(mysock);
		}
	} while (1);

	return 0;
}
