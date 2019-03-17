/* A simple server in the internet domain using TCP the port number is passed as an argument */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(char *msg)//method for returning error
{
perror(msg);
exit(1);
}

int main(int argc, char *argv[])//argc num of count argv variables
{

int sockfd, newsockfd, portno, clilen;
char buffer[256];//handle all values from server 
struct sockaddr_in serv_addr, cli_addr;
int n;

//check command line argument whether its given or not
if (argc < 2)
{
fprintf(stderr,"ERROR, no port provided\n");
exit(1);
}


//create a socket
sockfd = socket(AF_INET, SOCK_STREAM, 0);

//check if socket is done
if (sockfd < 0)
{
error("ERROR opening socket");
}
 
bzero((char *) &serv_addr, sizeof(serv_addr));

//get ready server address
portno = atoi(argv[1]);

serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = INADDR_ANY;
serv_addr.sin_port = htons(portno);


//bind socket and server address 
if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
{
error("ERROR on binding");
}


//go into listening mode  setting a timer to listen to 5 percent
listen(sockfd,5);
clilen = sizeof(cli_addr);

//creating client address,all client sddresses in their new 
newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);

if (newsockfd < 0)
{
error("ERROR on accept");
}

//clear buffer
bzero(buffer,256);

//reading the value from new socket empty to the buffer and writing thye new value to the socket 
n = read(newsockfd,buffer,255);

if (n < 0)
{
error("ERROR reading from socket");
}

printf("Here is the message: %s\n",buffer);

n = write(newsockfd,"I got your message",18);

if (n < 0)
{
error("ERROR writing to socket");
}
return 0;
}