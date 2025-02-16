extern "C"
{
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
}

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "proto.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 1234

int establish_connection(const char *ip_address, uint16_t port)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        std::cerr << "Error creating socket." << std::endl;
        return -1;
    }

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);

    if (inet_pton(AF_INET, ip_address, &server_address.sin_addr) <= 0)
    {
        std::cerr << "Error converting IP address." << std::endl;
        close(socket_fd);
        return -1;
    }

    if (connect(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        std::cerr << "Error connecting to server." << std::endl;
        close(socket_fd);
        return -1;
    }

    return socket_fd;
}

void process_challenge(challenge_unit &challenge)
{
    if (challenge.op == ADD)
    {
        challenge.answer = challenge.lhs + challenge.rhs;
    }
    else if (challenge.op == SUB)
    {
        challenge.answer = challenge.lhs - challenge.rhs;
    }
    else if (challenge.op == MUL)
    {
        challenge.answer = challenge.lhs * challenge.rhs;
    }
    else if (challenge.op == LEFT_SHIFT)
    {
        challenge.answer = challenge.lhs << (challenge.rhs % 32);
    }
    else if (challenge.op == RIGHT_SHIFT)
    {
        challenge.answer = challenge.lhs >> (challenge.rhs % 32);
    }
    else
    {
        std::cerr << "Operation not recognized!" << std::endl;
    }
}

int main()
{
    while (true)
    {
        int socket_fd = establish_connection(SERVER_IP, SERVER_PORT);
        if (socket_fd < 0)
        {
            std::cerr << "Connection to the server failed." << std::endl;
            return EXIT_FAILURE;
        }

        message_unit message;
        challenge_unit challenge;
        memset(&message, 0, sizeof(message));
        memset(&challenge, 0, sizeof(challenge));

        ssize_t received_bytes = recv(socket_fd, &message, sizeof(message), 0);
        if (received_bytes <= 0)
        {
            std::cerr << "Message reception failed." << std::endl;
            close(socket_fd);
            continue;
        }

        if (message.msg_type == CHALLENGE)
        {
            received_bytes = recv(socket_fd, &challenge, sizeof(challenge), 0);
            if (received_bytes <= 0)
            {
                std::cerr << "Challenge reception failed." << std::endl;
                close(socket_fd);
                continue;
            }

            process_challenge(challenge);

            ssize_t sent_bytes = send(socket_fd, &message, sizeof(message), 0);
            if (sent_bytes <= 0)
            {
                std::cerr << "Error sending message." << std::endl;
                close(socket_fd);
                continue;
            }

            sent_bytes = send(socket_fd, &challenge, sizeof(challenge), 0);
            if (sent_bytes <= 0)
            {
                std::cerr << "Error sending challenge." << std::endl;
                close(socket_fd);
                continue;
            }

            received_bytes = recv(socket_fd, &message, sizeof(message), 0);
            if (received_bytes <= 0)
            {
                std::cerr << "Server response reception failed." << std::endl;
                close(socket_fd);
                continue;
            }

            if (message.msg_type == SERVER_INFO)
            {
                if (message.server_info == CORRECT)
                {
                    std::cout << "Challenge solved successfully." << std::endl;
                }
                else
                {
                    std::cerr << "Challenge solution incorrect." << std::endl;
                    close(socket_fd);
                    return EXIT_FAILURE;
                }
            }
        }

        close(socket_fd);
    }

    return EXIT_SUCCESS;
}
