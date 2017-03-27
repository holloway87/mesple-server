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
