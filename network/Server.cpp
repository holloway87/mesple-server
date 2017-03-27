/**
 * @author Thomas Rudolph <me@holloway-web.de>
 * @since 2017.03.27
 */

#include <cstring>
#include <unistd.h>
#include <sys/socket.h>

#include "Server.hpp"
#include "ServerException.hpp"

/**
 * New instance with the given server port.
 *
 * @param port
 */
Server::Server(const string port) {
    serverPort = port;
}

/**
 * Binds the socket for incoming connections.
 */
void Server::bindSocket() {
    int status;
    struct addrinfo *info;

    for (info = serverInfo; NULL != info; info = info->ai_next) {
        serverSocket = socket(info->ai_family, info->ai_socktype, info->ai_protocol);

        if (-1 == serverSocket) {
            continue;
        }

        status = bind(serverSocket, info->ai_addr, info->ai_addrlen);
        if (-1 == status) {
            continue;
        }

        break;
    }

    if (NULL == info) {
        if (-1 == serverSocket) {
            throw ServerException("error: could not bind to port " + serverPort + ": " + strerror(errno),
                                  ServerException::CODE_BIND_ERROR);
        } else {
            string message = "error: could not create socket: ";
            message += strerror(errno);

            throw ServerException(message, ServerException::CODE_SOCKET_ERROR);
        }
    }
}

/**
 * Initialize the server connectivity.
 */
void Server::init() {
    setServerInfo();
    bindSocket();
}

/**
 * Set the address info for the server.
 */
void Server::setServerInfo() {
    int status;
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    status = getaddrinfo(NULL, serverPort.c_str(), &hints, &serverInfo);
    if (0 != status) {
        string message = "failed to get own address info: ";
        message += gai_strerror(status);

        throw ServerException(message, ServerException::CODE_NO_ADDRESS_INFO);
    }
}

/**
 * Close connections and free resources.
 */
void Server::shutdown() {
    freeaddrinfo(serverInfo);
    if (0 <= serverSocket) {
        close(serverSocket);
    }
}
