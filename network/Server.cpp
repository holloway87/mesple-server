/**
 * @author Thomas Rudolph <me@holloway-web.de>
 * @since 2017.03.27
 */

#include <cstring>

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
 * Initialize the server connectivity.
 */
void Server::init() {
    setServerInfo();
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
}
