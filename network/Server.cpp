/**
 * @author Thomas Rudolph <me@holloway-web.de>
 * @since 2017.03.27
 */

#include <arpa/inet.h>
#include <csignal>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <thread>

#include "Server.hpp"
#include "ServerException.hpp"

/**
 * Determines if the server is running.
 */
bool Server::running;

/**
 * New instance with the given server port.
 *
 * @param port
 */
Server::Server(const string port) {
    running = true;
    serverPort = port;
}

/**
 * Check for new clients and add them.
 *
 * @since 2017.03.29
 */
void Server::addNewClients() {
    vector<Client> newClients = connectionManager->getNewClients();
    if (newClients.empty()) {
        return;
    }

    for (vector<Client>::iterator it = newClients.begin(); it != newClients.end(); ++it) {
        clients.push_back(*it);

        cout << "added client: " << getClientAddress(*it) << endl;
    }
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
            string message = "error: could not create socket: ";
            message += strerror(errno);

            throw ServerException(message, ServerException::CODE_SOCKET_ERROR);
        } else {
            throw ServerException("error: could not bind to port " + serverPort + ": " + strerror(errno),
                                  ServerException::CODE_BIND_ERROR);
        }
    }
}

/**
 * Return the client ip as a string representation.
 *
 * @since 2017.03.29
 * @param client
 * @return ip address as string
 */
string Server::getClientAddress(Client client) {
    char s[INET6_ADDRSTRLEN];
    string result;

    struct sockaddr_storage clientAddress = client.getAddress();
    inet_ntop(clientAddress.ss_family, getInAddress((struct sockaddr *) &clientAddress), s, sizeof s);
    result = s;

    return result;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
/**
 * Get the correct address structure, depending on the ip type.
 *
 * @since 2017.03.29
 * @param address socket address structure
 * @return ipv4 or ipv6 address structure
 */
void *Server::getInAddress(struct sockaddr *address) {
    if (address->sa_family == AF_INET) {
        return &(((struct sockaddr_in*) address)->sin_addr);
    }

    return &(((struct sockaddr_in6*) address)->sin6_addr);
}
#pragma clang diagnostic pop

/**
 * Initialize the server connectivity.
 */
void Server::init() {
    signal(SIGKILL, Server::signalHandler);
    signal(SIGINT, Server::signalHandler);
    signal(SIGTERM, Server::signalHandler);

    setServerInfo();
    bindSocket();
    startListen();
}

/**
 * Main loop for incoming connections.
 */
void Server::loop() {
    connectionManager = new ConnectionManager(serverSocket);
    thread connectionThread(&ConnectionManager::loop, connectionManager);

    while (running) {
        addNewClients();
    }

    connectionManager->running = false;
    // shutdown server socket to abort the current accept call on the connection manager
    shutdown(serverSocket, 2);
    connectionThread.join();
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
void Server::shutdownServer() {
    freeaddrinfo(serverInfo);
    if (0 <= serverSocket) {
        close(serverSocket);
    }
}

/**
 * Start to listen for connections.
 */
void Server::startListen() {
    int status;

    status = listen(serverSocket, 20);
    if (-1 == status) {
        string message = "error: could not start to listen on port";
        message += strerror(errno);

        throw ServerException(message, ServerException::CODE_LISTEN_ERROR);
    }
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
/**
 * Stops the server via a signal.
 *
 * @param signal
 */
void Server::signalHandler(int signal) {
    running = false;
}
#pragma clang diagnostic pop
