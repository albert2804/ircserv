#include "Channel.Class.hpp"

Channel::Channel() : _channelName("Unknown"), _topicMessage("None"), \
					 _topic_restricted(true), _invite_only(false), \
					_passPhrase(""), _userlimit(-1) {}

Channel::Channel(std::string name) : _channelName(name), _topicMessage("None"), \
					 _topic_restricted(false), _invite_only(false), \
					_passPhrase(""), _userlimit(-1) {}

Channel::Channel(std::string name, bool topic, bool invite, std::string pass, int userlimit) : \
					_channelName(name),  _topicMessage("None"), \
					_topic_restricted(topic), _invite_only(invite), \
					_passPhrase(pass), _userlimit(userlimit) {}


//priviliges are given to a user
int Channel::give_priveleges(std::string cli) {

	if (VERBOSE)
		std::cout << "give_privileges" << std::endl;

	std::map<std::string, bool>::iterator it = _users.find(cli);
	if (it != _users.end()) {
		it->second = true;
		return (1);
	}
	else {
		if (DEBUG)
			std::cout << "No User found, returned 0" << std::endl;
		return (0);
	}
}

// priviliges are removed
int Channel::rm_priveleges(std::string cli) {

	if (VERBOSE)
		std::cout << "remove_privileges" << std::endl;

	std::map<std::string, bool>::iterator it = _users.find(cli);
	if (it != _users.end()) {
		it->second = false;
		return (1);
	}
	else {
		if (DEBUG)
			std::cout << "No User found, returned 0" << std::endl;
		return (0);
	}
}

/*
   The JOIN command is used by a user to request to start listening to
   the specific channel.  Servers MUST be able to parse arguments in the
   form of a list of target, but SHOULD NOT use lists when sending JOIN
   messages to clients.

   Once a user has joined a channel, he receives information about
   all commands his server receives affecting the channel.  This
   includes JOIN, MODE, KICK, PART, QUIT and of course PRIVMSG/NOTICE.
   This allows channel members to keep track of the other channel
   members, as well as channel modes.

   If a JOIN is successful, the user receives a JOIN message as
   confirmation and is then sent the channel's topic (using RPL_TOPIC) and
   the list of users who are on the channel (using RPL_NAMREPLY), which
   MUST include the user joining.

   Note that this message accepts a special argument ("0"), which is
   a special request to leave all channels the user is currently a member
   of.  The server will process this message as if the user had sent
   a PART command (See Section 3.2.2) for each channel he is a member
   of.
*/
int Channel::join(std::string cli) {

	if (VERBOSE)
		std::cout << "join" << std::endl;

	std::map<std::string, bool>::iterator it = _users.find(cli);
	if (it == _users.end()) {
		_users[cli] = false;
		return (1);
	}
	else {
		if (DEBUG)
			std::cout << "User already exists, returned 0" << std::endl;
		return (0);
	}
}

/*
   The KICK command can be used to request the forced removal of a user
   from a channel.  It causes the <user> to PART from the <channel> by
   force.  For the message to be syntactically correct, there MUST be
   either one channel parameter and multiple user parameter, or as many
   channel parameters as there are user parameters.  If a "comment" is
   given, this will be sent instead of the default message, the nickname
   of the user issuing the KICK.

   The server MUST NOT send KICK messages with multiple channels or
   users to clients.  This is necessarily to maintain backward
   compatibility with old client software.
*/
int Channel::kick(std::string to_kick) {
	
	if (VERBOSE)
		std::cout << "kick" << std::endl;

	std::map<std::string, bool>::iterator it = _users.find(to_kick);
	if (it != _users.end()) {
		_users.erase(to_kick);
		return (1);
	}
	else {
		if (DEBUG)
			std::cout << "User not found, returned 0" << std::endl;
		return (0);
	}
}

/*
   The INVITE command is used to invite a user to a channel.  The
   parameter <nickname> is the nickname of the person to be invited to
   the target channel <channel>.  There is no requirement that the
   channel the target user is being invited to must exist or be a valid
   channel.  However, if the channel exists, only members of the channel
   are allowed to invite other users.  When the channel has invite-only
   flag set, only channel operators may issue INVITE command.

   Only the user inviting and the user being invited will receive
   notification of the invitation.  Other channel members are not
   notified.  (This is unlike the MODE changes, and is occasionally the
   source of trouble for users.)
*/
// int Channel::invite(std::string to_invite) {
	
// 	if (VERBOSE)
// 		std::cout << "invite" << std::endl;

// 	std::map<std::string, bool>::iterator it = _users.find(to_invite);
// 	if (it != _users.end()) {
// 		_users.(to_kick);
// 		return (1);
// 	}
// 	else {
// 		if (DEBUG)
// 			std::cout << "User not found, returned 0" << std::endl;
// 		return (0);
// 	}
// }

/*
   The TOPIC command is used to change or view the topic of a channel.
   The topic for channel <channel> is returned if there is no <topic>
   given.  If the <topic> parameter is present, the topic for that
   channel will be changed, if this action is allowed for the user
   requesting it.  If the <topic> parameter is an empty string, the
   topic for that channel will be removed.
*/
int Channel::topic(std::string topic_message) {
	
	if (VERBOSE)
		std::cout << "Set new topic message" << std::endl;

	set_topic(topic_message);
	return (1);
}

int Channel::view_topic(void) {
	
	if (VERBOSE)
		std::cout << "Display topic message" << std::endl;

	std::cout << get_topic() << std::endl;
	return (1);
}

/*
3.2.3 Channel mode message

      Command: MODE
   Parameters: <channel> *( ( "-" / "+" ) *<modes> *<modeparams> )

   The MODE command is provided so that users may query and change the
   characteristics of a channel.  For more details on available modes
   and their uses, see "Internet Relay Chat: Channel Management" [IRC-
   CHAN].  Note that there is a maximum limit of three (3) changes per
   command for modes that take a parameter.
*/
// Channel& Channel::modes(bool privileges, char alter, std::string mode) {

// }

//==============================================================================
//Debugging
void Channel::list_clients(void) {

	if (VERBOSE)
		std::cout << "list_clients" << std::endl;

	std::map<std::string, bool>::iterator it = _users.begin();
	for ( ; it != _users.end(); it++) {
		std::cout << "Client: " << it->first << " Privilieges: " << it->second << std::endl;
	}
	std::cout << "--------------------" << std::endl;
}

void Channel::list_channel_attributes(void) {

	if (VERBOSE)
		std::cout << "list_attributes" << std::endl;

		std::cout << "ChannelName: " << _channelName << std::endl;
		std::cout << "TopicMessage: " << _topicMessage << std::endl;
		std::cout << "Topic restricted?: " << _topic_restricted << std::endl;
		std::cout << "Invite Only? " << _invite_only << std::endl;
		std::cout << "Password: " << _passPhrase << std::endl;
		std::cout << "Userlimit: " << _userlimit << std::endl;
	std::cout << "--------------------" << std::endl;

}


//==============================================================================
//setter
void Channel::set_users(std::map<std::string, bool> users) {_users = users;}
void Channel::set_topic(std::string message) {_topicMessage = message;}
void Channel::set_topic_restriction(bool restriction) {_topic_restricted = restriction;}
void Channel::set_invite_only(bool restriction) {_invite_only = restriction;}
void Channel::set_passphrase(std::string passphrase) {_passPhrase = passphrase;}
void Channel::set_userlimit(int limit) {_userlimit = limit;}

//getter
std::map<std::string, bool> Channel::get_users(void) {return (_users);}
std::string Channel::get_topic(void) {return (_topicMessage);}
bool Channel::get_topic_restriction(void) {return (_topic_restricted);}
bool Channel::get_invite_only(void) {return (_invite_only);}
std::string Channel::get_passphrase(void) {return (_passPhrase);}
int Channel::get_userlimit(void) {return (_userlimit);}