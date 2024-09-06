#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <ip_address> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *ip_address_str = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in dest; /* socket info about the machine connecting to us */
    struct sockaddr_in serv; /* socket info about our server */
    int mysocket;            /* socket used to listen for incoming connections */
    unsigned int socksize = sizeof(struct sockaddr);

    memset(&dest, 0, sizeof(dest)); /* zero the struct before filling the fields */
    serv.sin_family = AF_INET;      /* set the type of connection to TCP/IP */
    
    // Convert IP address from string to binary form
    if (inet_aton(ip_address_str, &serv.sin_addr) == 0) {
        perror("Invalid IP address");
        exit(EXIT_FAILURE);
    }

    serv.sin_port = htons(port); /* set the server port number */

    mysocket = socket(AF_INET, SOCK_STREAM, 0);

    /* start listening, allowing a queue of up to 1 pending connection */
    listen(mysocket, 1);

    int consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);

    printf("Incoming connection from %s - sending welcome\n", inet_ntoa(dest.sin_addr));

    char msg[15] = "Hello World !\n";
    if (send(consocket, msg, strlen(msg), 0) > 0)
        printf("Message sent to the client\n");

    close(consocket);
    close(mysocket);
    exit(EXIT_SUCCESS);
}