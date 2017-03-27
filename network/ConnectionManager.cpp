/**
 * @author Thomas Rudolph <me@holloway-web.de>
 * @since 2017.03.27
 */

#include "ConnectionManager.hpp"

/**
 * New instance with the given server socket.
 *
 * @param socket
 */
ConnectionManager::ConnectionManager(int socket) {
    running = true;
    serverSocket = socket;
}

/**
 * Determines if the connection manager awaiting new connections.
 */
bool ConnectionManager::running;

/**
 * Main loop to accept connections.
 */
void ConnectionManager::loop() {
    socklen_t addressLength;
    int clientSocket;
    struct sockaddr_storage newAddress;
    vector<Client>::iterator it;

    while (running) {
        addressLength = sizeof(newAddress);
        clientSocket = accept(serverSocket, (struct sockaddr *) &newAddress, &addressLength);

        if (-1 == clientSocket) {
            continue;
        }

        Client client {newAddress, clientSocket};
        it = clients.end();
        clients.insert(it, client);
    }
}
