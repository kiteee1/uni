extern "C"
{
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/random.h>
#include <errno.h>
}

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "proto.h"

#define SERVER_PORT 1234
#define BACKLOG 10

void create_challenge(challenge_unit &challenge)
{
    uint32_t random_values[3];
    ssize_t result = getrandom(random_values, sizeof(random_values), 0);
    if (result != sizeof(random_values))
    {
        std::cerr << "Error generating random values." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    challenge.op = random_values[0] % OP_END;
    challenge.lhs = random_values[1];
    challenge.rhs = random_values[2];
    challenge.answer = 0;
}

int initialize_server_socket(uint16_t port)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        std::cerr << "Socket creation failed." << std::endl;
        return -1;
    }

    int opt_val = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(opt_val));

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);

    if (bind(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        std::cerr << "Binding socket failed." << std::endl;
        close(socket_fd);
        return -1;
    }

    if (listen(socket_fd, BACKLOG) < 0)
    {
        std::cerr << "Listening on socket failed." << std::endl;
        close(socket_fd);
        return -1;
    }

    return socket_fd;
}

void manage_client(int client_socket)
{
    message_unit message;
    challenge_unit challenge;
    memset(&message, 0, sizeof(message));
    memset(&challenge, 0, sizeof(challenge));

    message.msg_type = CHALLENGE;
    create_challenge(challenge);

    if (send(client_socket, &message, sizeof(message), 0) <= 0)
    {
        std::cerr << "Failed to send message." << std::endl;
        close(client_socket);
        return;
    }

    if (send(client_socket, &challenge, sizeof(challenge), 0) <= 0)
    {
        std::cerr << "Failed to send challenge." << std::endl;
        close(client_socket);
        return;
    }

    if (recv(client_socket, &message, sizeof(message), 0) <= 0)
    {
        std::cerr << "Failed to receive message." << std::endl;
        close(client_socket);
        return;
    }

    if (message.msg_type != CHALLENGE)
    {
        std::cerr << "Invalid message type received!" << std::endl;
        message.msg_type = SERVER_INFO;
        message.server_info = WRONG;
        send(client_socket, &message, sizeof(message), 0);
        close(client_socket);
        return;
    }

    challenge_unit client_response;
    if (recv(client_socket, &client_response, sizeof(client_response), 0) <= 0)
    {
        std::cerr << "Failed to receive challenge response." << std::endl;
        close(client_socket);
        return;
    }

    bool is_correct = true;
    uint32_t expected_answer = 0;

    if (client_response.lhs != challenge.lhs || client_response.rhs != challenge.rhs || client_response.op != challenge.op)
    {
        is_correct = false;
    }
    else
    {
        if (client_response.op == ADD)
        {
            expected_answer = client_response.lhs + client_response.rhs;
        }
        else if (client_response.op == SUB)
        {
            expected_answer = client_response.lhs - client_response.rhs;
        }
        else if (client_response.op == MUL)
        {
            expected_answer = client_response.lhs * client_response.rhs;
        }
        else if (client_response.op == LEFT_SHIFT)
        {
            expected_answer = client_response.lhs << (client_response.rhs % 32);
        }
        else if (client_response.op == RIGHT_SHIFT)
        {
            expected_answer = client_response.lhs >> (client_response.rhs % 32);
        }
        else
        {
            is_correct = false;
            std::cerr << "Unrecognized operation received!" << std::endl;
        }
        if (client_response.answer != expected_answer)
        {
            is_correct = false;
        }
    }

    message.msg_type = SERVER_INFO;
    message.server_info = is_correct ? CORRECT : WRONG;

    if (send(client_socket, &message, sizeof(message), 0) <= 0)
    {
        std::cerr << "Failed to send server information." << std::endl;
    }

    close(client_socket);
}

int main()
{
    int server_socket = initialize_server_socket(SERVER_PORT);
    if (server_socket < 0)
    {
        return EXIT_FAILURE;
    }

    std::cout << "Server running on port " << SERVER_PORT << std::endl;

    while (true)
    {
        struct sockaddr_in client_address;
        socklen_t client_address_length = sizeof(client_address);
        int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_length);
        if (client_socket < 0)
        {
            std::cerr << "Error accepting client connection." << std::endl;
            continue;
        }

        manage_client(client_socket);
    }

    close(server_socket);
    return EXIT_SUCCESS;
}
