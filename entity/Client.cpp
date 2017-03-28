/**
 * @author Thomas Rudolph <me@holloway-web.de>
 * @since 2017.03.27
 */

#include "Client.hpp"

/**
 * New instance with given address and socket.
 *
 * @param address
 * @param clientSocket
 */
Client::Client(struct sockaddr_storage address, int clientSocket) {
    this->address = address;
    this->clientSocket = clientSocket;
}

/**
 * Get the address structure.
 *
 * @since 2017.03.29
 * @return address structure
 */
struct sockaddr_storage Client::getAddress() {
    return address;
}

/**
 * Return the socket descriptor.
 *
 * @since 2017.03.29
 * @return socket descriptor
 */
int Client::getSocket() {
    return clientSocket;
}
