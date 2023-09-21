/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.Class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:27:08 by kczichow          #+#    #+#             */
/*   Updated: 2023/09/21 11:22:16 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <fcntl.h>
#include <poll.h>
#include <vector>
#include <unistd.h>

#include "defines.hpp"
#include "Client.Class.hpp"

typedef	struct s_msg{
		std::string					prefix;
		std::string					command;
		std::string					param;
		std::vector<std::string>	paramVec;
} t_msg;

class Server{

    private:
        int							_port;
        std::string					_password;
		std::string					_hostname;

        int							_serverSocket;
		struct sockaddr_in			_serverAddr;
		struct pollfd				_serverPollfd;
		std::vector<Client>			_clients;
		std::vector<pollfd>			_fds;
		Server();

		int setupServer();
		void acceptNewClient();
		void handleClient(Client &client);

	public:
		~Server();
		Server(int port, std::string password);
		Server (Server const &src);
		Server &operator= (Server const &src);

		void runServer();

		std::string numReply(int errorCode, t_msg *message, Client client);

		int pass(t_msg *message, Client client);
};