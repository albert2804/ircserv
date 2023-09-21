#pragma once

#include <iostream>
#include <string>
#include <map>

#include "defines.hpp"
#include "Client.Class.hpp"

class Channel {
	
	protected:
		std::string _channelName;
		std::map<std::string, bool> _users; //has all users and their operator flag
		std::string _topicMessage; // standard topic message is: "None"
		bool _topic_restricted; //if true only operators can alter the topic_message
		bool _invite_only;
		std::string _passPhrase; // if empty, the channel is not pw_limited
		int _userlimit; //if <=0, the channel is unlimited

	public:

		//Canonical Form
		Channel();
		Channel(std::string name);
		Channel(std::string name, bool topic, bool invite, std::string pass, int userlimit);

		
		int give_priveleges(std::string cli); //changes operator/kick-flag or adds a user if not in the container, returns 1 if succesfull
		int rm_priveleges(std::string cli); //changes operator/kick-flag or adds a user if not in the container, returns 1 if succesfull
		int join(std::string cli); //a client joins the channel
		
		//operator functions
		int kick(std::string to_kick); //returns 1 if successfull
		int invite(std::string to_invite); //returns 1 if successfull
		int topic(std::string topic_message); //If an empty string is given, the topic will be removed, otherwise it will be changed to new mesage
		int view_topic(); //second topic function for the case, that no topic_parameter is entered, it displays the latest topic message
		//alters the mode of a channel, e.g. #teest +l 10 (limit of 10 users on channel #teest)
		class Channel& modes(bool privileges, char alter, std::string mode); //returns a reference to the new channel

		//Debugging
		void list_clients(); //lists all clients in the channel and their privileges
		void list_channel_attributes(void);
		//setters
		void set_users(std::map<std::string, bool> users);
		void set_topic(std::string message);
		void set_topic_restriction(bool restriction);
		void set_invite_only(bool restriction);
		void set_passphrase(std::string passphrase);
		void set_userlimit(int limit);
		
		//getters
		std::map<std::string, bool> get_users(void);
		std::string get_topic(void);
		bool get_topic_restriction(void);
		bool get_invite_only(void);
		std::string get_passphrase(void);
		int get_userlimit(void);
};