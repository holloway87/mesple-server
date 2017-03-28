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
 * Returns all new clients.
 *
 * Clears the clients vector afterwards.
 *
 * @since 2017.03.29
 * @return a copy of all new clients
 */
vector<Client> ConnectionManager::getNewClients() {
    lock_guard<mutex> guard {clientsMutex};
    vector<Client> clientsCopy {clients};

    clients.clear();

    return clientsCopy;
}

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
        clientsMutex.lock();
        it = clients.end();
        clients.insert(it, client);
        clientsMutex.unlock();
    }
}
