#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_MSG_SIZE 1024

/* Error handling function */
void DieWithError(char *errorMessage) {
    perror(errorMessage);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientLen = sizeof(clientAddr);
    char buffer[MAX_MSG_SIZE];

    // Create socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        DieWithError("socket() failed");
    }

    // Initialize server address struct
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(atoi(argv[1]));

    // Bind the socket
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        DieWithError("bind() failed");
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) < 0) {
        DieWithError("listen() failed");
    }

    printf("Server is listening on port %s...\n", argv[1]);

    // Accept incoming connection
    if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientLen)) < 0) {
        DieWithError("accept() failed");
    }

    printf("Accepted connection from %s\n", inet_ntoa(clientAddr.sin_addr));

    // Receive and echo data back to the client
    ssize_t received;
    while ((received = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[received] = '\0';
        printf("Received: %s", buffer);

        // Echo back to the client
        if (send(clientSocket, buffer, received, 0) != received) {
            DieWithError("send() failed");
        }
    }

    if (received == 0) {
        printf("Client disconnected.\n");
    } else if (received < 0) {
        DieWithError("recv() failed");
    }

    // Close the sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}