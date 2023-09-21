/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.Class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:27:01 by kczichow          #+#    #+#             */
/*   Updated: 2023/09/20 17:46:29 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Server.Class.hpp"

/* ---------------- CANONICAL FORM ---------------------------*/
Server::Server() : _port(0), _password("no_pw"){
	this->_fds[MAX_EVENTS];
};

Server::Server(int port, std::string password) : _port(port), _password(password){};

Server::~Server(){};

Server::Server (Server const &src){ (void) src;};

Server &Server::operator= (Server const &src){
    this->_serverSocket = src._serverSocket;
    this->_port = src._port;
    this->_password = src._password;
    return (*this);
};


/* ------------------------- PRIVATE METHODS ---------------------------------*/
void Server::handleClient(Client &client){
	char buffer[1024];
	while (true) {
		memset(buffer, 0, sizeof(buffer));
		int bytesRead = recv(client.getClientSocket(), buffer, sizeof(buffer), 0);
		
		if (bytesRead == -1) {
				// Handle other errors.
				perror("recv");
				break;
		} else if (bytesRead == 0) {
			// The client has closed the connection.
			break;
		} else {
			// Process the received data.
			std::string message(buffer);
			std::cout << "Received: " << message << std::endl;
		}
	}
}
// void Server::handleClient(Client &client){

//     std::cout << "\thandle client function accessed" << std::endl; 
// 	char buffer[1024];
// 	// while (true) {
// 		memset(buffer, 0, sizeof(buffer));
// 		// std::cout << "client socket in handle client " << client.getClientSocket() << std::endl;
// 		int bytesRead = recv(client.getClientSocket(), buffer, sizeof(buffer), 0);
// 		std::string message(buffer);
// 		std::cout << "\tbytesRead: " << bytesRead << std::endl;
// 		// if (bytesRead != -1)
// 		// 	std::cout << "Bytes read:" << bytesRead << std::endl;
// 		if (bytesRead == 1){
// 			// remove client
// 			// close(client.getClientSocket());
// 			// std::cout << "Client disconnected" << std::endl;
// 			// close (_serverSocket);
// 			// break ;
// 		}
// 		if (bytesRead > 0){
// 		std::string message(buffer);
// 		std::cout << "\treceived: " << message << std::endl;
// 		}
// 	// }
// }

void Server::acceptNewClient(){

	Client     newClient;

    socklen_t   clientAddrLen = sizeof(newClient.getClientAddr());
    newClient.setClientSocket(accept(this->_serverSocket,reinterpret_cast<struct sockaddr *>(&newClient.getClientAddr()), &clientAddrLen));


	if (newClient.getClientSocket() == -1){
        std::cerr << "Error accepting client connection\n";
    }

	//insert prompt and checks for nickname, username and password;

    std::cout << "Client connected\n";

	newClient.setClientPollfdFD(newClient.getClientSocket());
	newClient.setClientPollfdEvents(POLLIN);

    // set new client to non-blocking mode
    fcntl(newClient.getClientSocket(), F_SETFL, O_NONBLOCK);

    // add new client socket to pollfds and client to clients vector
    this->_clients.push_back(newClient);
    this->_fds.push_back(newClient.getClientPollfd());

    std::cout << "new client added to list of known clients on socket " << newClient.getClientSocket() << " at address " << &_clients.back() << "\n";
}

int Server::setupServer(){
	close (3);

	// create serversocket
	_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (_serverSocket == -1){
		std::cerr << "Error creating socket\n" ;
		return 1;
	}

	// bind serversocket, using internet style (struct sockaddr_in)
	this->_serverAddr.sin_family = AF_INET;
	this->_serverAddr.sin_port = htons(this->_port);
	// this->_serverAddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	this->_serverAddr.sin_addr.s_addr = INADDR_ANY;
	if (bind(_serverSocket, reinterpret_cast<struct sockaddr*>(&this->_serverAddr), sizeof(this->_serverAddr)) == -1) {
		std::cerr << "Error binding socket\n";
		return 1;
	}

	// set server to listen
	if (listen(this->_serverSocket, MAX_CONNECTIONS) == -1){
		std::cerr << "Error listening on socket\n";
		return 1;
	}

	// set serversocket to non-blocking mode
	fcntl(this->_serverSocket, F_SETFL, O_NONBLOCK);

	_serverPollfd.fd = this->_serverSocket;
	_serverPollfd.events = POLLIN;
	this->_fds.push_back(this->_serverPollfd);
	// this->_nfds = 1;

	std::cout << "Server listening on port " << this->_port << std::endl;
	return 0;
}


/* ------------------------- PUBLIC METHODS ----------------------------------*/

void Server::runServer(){

	setupServer();

	while (true){
		// set poll with unlimited time
		int PollResult = poll(_fds.data(), _fds.size(), -1);
		
		if (LOOP)
			std::cout << "PollResult" << PollResult << std::endl;
		
		if (PollResult == -1){
			perror("poll");
			continue;
		}

		if (this->_fds[0].revents & POLLIN)
			acceptNewClient();
		

		for (unsigned long i = 0; i < _fds.size(); ++i) {
			
			if (LOOP)
				std::cout << "Revents" << _fds[i].revents << std::endl;
				
			if(_fds[i].revents & POLLIN){
				std::cout << "Client to handle " << i << std::endl;
				handleClient(_clients[i]);
				// send_message_to_client(_clients[i]);
			}
		}
			if (LOOP)
				std::cout << "========================" << std::endl;

        // command 
            // receive / send
        // remove client (close)
	}
	for (int i = 1; i < _clients.size(); ++i){
		close(_clients[i].getClientSocket());
	}
	close (_serverSocket);
};