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
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_ip> <server_port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[MAX_MSG_SIZE];

    // Create socket
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        DieWithError("socket() failed");
    }

    // Initialize server address struct
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    serverAddr.sin_port = htons(atoi(argv[2]));

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        DieWithError("connect() failed");
    }

    printf("Connected to server %s:%s\n", argv[1], argv[2]);

    // Read input from the user and send to the server
    while (1) {
        printf("Enter message (or 'quit' to exit): ");
        fgets(buffer, sizeof(buffer), stdin);

        if (strcmp(buffer, "quit\n") == 0) {
            break;
        }

        if (send(clientSocket, buffer, strlen(buffer), 0) != strlen(buffer)) {
            DieWithError("send() failed");
        }

        // Receive the echoed message from the server
        ssize_t received = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (received <= 0) {
            DieWithError("recv() failed");
        }

        buffer[received] = '\0';
        printf("Received from server: %s", buffer);
    }

    // Close the socket
    close(clientSocket);

    return 0;
}