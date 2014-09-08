/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h> //for standard i/o
#include <stdlib.h> 
#include <string.h>
#include <sys/types.h> // for data types definitions used in system calls
#include <sys/time.h>
#include <unistd.h>
#include <sys/socket.h> //definition of structures needed for sockets
#include <netinet/in.h> // constants and structures for internet domain

void error(const char *msg)
{
    perror(msg); //called when a sys call fails. Displays the error on stderror and exits the program
    exit(1);
}

int main(int argc, char *argv[])
{
     int socket_file_descriptor, new_socket_file_descriptor, portno, n; //n is the chars read or written
     socklen_t client_address_length;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     fd_set rfds;
     struct timeval tv;
     int retval, nfd;


     //Check for the right arguments
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }

     FD_ZERO(&rfds);
     socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
     if (socket_file_descriptor < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno); // converts portno to Network byte order
     if (bind(socket_file_descriptor, (struct sockaddr *) &serv_addr, sizeof(serv_addr))
             < 0) 
              error("ERROR on binding");
     listen(socket_file_descriptor,5);
     client_address_length = sizeof(cli_addr);
     
     /*first select => Before accept() */
     FD_SET(socket_file_descriptor,&rfds);
     nfd = socket_file_descriptor+1;
     tv.tv_sec = 0;
     tv.tv_usec = 0;
     do {
     retval = select(nfd,&rfds,NULL,NULL, &tv);
     } while(retval == -1);
     

     new_socket_file_descriptor = accept(socket_file_descriptor, 
                 (struct sockaddr *) &cli_addr, 
                 &client_address_length);
     if (new_socket_file_descriptor < 0) 
             error("ERROR on accept");
     
     /*second select => Before read*/
     FD_ZERO(&rfds);
     FD_SET(new_socket_file_descriptor,&rfds);
     nfd = new_socket_file_descriptor + 1;
     retval = 0;
     do {
     retval = select(nfd, &rfds, NULL, NULL, &tv);
     } while(retval == -1);


     bzero(buffer,256);
     n = read(new_socket_file_descriptor,buffer,255); //(fro,to,length)
     if (n < 0) error("ERROR reading from socket");
     

     printf("Here is the message: %s\n",buffer);
     n = write(new_socket_file_descriptor,"I got your message",18);
     if (n < 0) error("ERROR writing to socket");
     
     close(new_socket_file_descriptor);
     close(socket_file_descriptor);
     
     return 0; 
}