#include "Server.Class.hpp"
#include "Client.Class.hpp"


std::string Server::numReply(int errorCode, t_msg *message, Client client){

	std::string reply;

	switch(errorCode){
		case RPL_WELCOME:
			reply =  ": " + this->_hostname + " 001 " + client.getNickName() + " :Welcome to the Internet Relay Network, " + client.getNickName() + "!" +client.getUserName() + "@" + this->_hostname;
			break;
		case RPL_YOURHOST:
			reply =  ": " + this->_hostname + " 002 " + client.getNickName() + " :Your host is " + this->_hostname + ", running on version 1.0 !";
			break;
		case ERR_NONICKNAMEGIVEN:
			reply =  ": " + this->_hostname + " 431 " + client.getNickName() + " :No nickname given\n";
			break;
		case ERR_ALREADYREGISTRED:
			reply = ": " + this->_hostname + " 462 " + client.getNickName() + " :You may not reregister\n";
			break;
		case ERR_NEEDMOREPARAMS:
			reply = ": " + this->_hostname + " 461 " + client.getNickName() + " :" +message->command + ": Not enough parameters";
			break;
		default:
			std::cout << "unkown error\n";
	}
	return NULL;
}

