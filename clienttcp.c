#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 

void error(char *msg)
{
perror(msg);
exit(0);
}

int main(int argc, char *argv[])
{
int sockfd, portno, n;
struct sockaddr_in serv_addr;
struct hostent *server;

char buffer[256];

//check command line arg is less than 3
if (argc < 3)
{
fprintf(stderr,"usage %s hostname port\n", argv[0]);
exit(0);
}

//get port number
portno = atoi(argv[2]);

//create socket
sockfd = socket(AF_INET, SOCK_STREAM, 0);

if (sockfd h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);

//convert host to network address
serv_addr.sin_port = htons(portno);


//creating connection
if (connect(sockfd,&serv_addr,sizeof(serv_addr)) < 0)
{
error("ERROR connecting");
}
//enter a value
printf("Please enter the message: ");
//clear a buffer
bzero(buffer,256);
fgets(buffer,255,stdin);
//write the value
n = write(sockfd,buffer,strlen(buffer));
if (n < 0)
{
error("ERROR writing to socket");
}
bzero(buffer,256);
//read socket into buffer
n = read(sockfd,buffer,255);
if (n < 0)
{
error("ERROR reading from socket");
}
printf("%s\n",buffer);

return 0;
}