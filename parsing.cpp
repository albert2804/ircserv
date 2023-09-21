#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
#include <exception>

//prototypes that i need later for parsing
//log in, authenticate client and create new user
void  logIn(std::string userName);
//nick, create nickname
void setNickName(std::string newNickName);
//user, create username
void setUserName(std::string newUserName);
//join, join a channel that is not invite-only
void joinChannel(std::string channelToJoin);
//op, make a user operator on channel or whole server
void setOperator(std::string nickName);
//prvmsg, write directly to another client or channel
void privateMessAge(std::string writeTo, std::string textToBeSent);

//all commands with uppercase need to be implemented like in IRC_protocol 
//KICK, eject a client from channel
void kick(std::vector<std::string> channelList, 
          std::vector<std::string> usersToKick, std::string commentToDisplay);

//INVITE, invite a client to a channel
void invite(std::string nickName, std::string channelToBeInvited);

//TOPIC, change or view the hannel topic, if setTopic is NULL -> view topic, if setTopic is emptyString -> remove all Topics in channel
std::string topic(std::string channelToChange);
std::string topic(std::string channelToChange, std::string setTopic);

//MODE, Change the channel mode
// +k set passwod, -k remove password
void  mode(std::string channelToChange, std::string modesFlag, std::string Message);
// +o set operator, -o remove operator
// +l set user limit to channel amount is user_limit, -l remove user limit
//+i set invite only channel, -i removce it
//+t set topic command to Operator only, -t topic command for regular users

void parsePrvMsg(std::string Message) {
  size_t      pos;
  std::string writeTo;

  pos = Message.find(' ');
  if (pos != std::string::npos) {
    writeTo = Message.substr(0, pos);
    Message.erase(0, pos + 1);
  } else {
    Message = "";
  }
  std::cout << "Pivate Message to " << writeTo << " " << Message << std::endl;
  // privateMessAge(writeTo, Message);
}

void  parseKick(std::string message) {
  (void)message;
}

void parseTopic(std::string Message) {
  size_t      pos;
  std::string channelToChange;

  pos = Message.find(' ');
  if (pos != std::string::npos) {
    channelToChange = Message.substr(0, pos);
    Message.erase(0, pos + 1);
    // topic(channelToChange, Message);
    std::cout << "Topic in " << channelToChange << "change to " << Message << std::endl;
    return;
  }
  std::cout << "Topic View " << Message << std::endl;
  // topic(Message);
}

void parseInvite(std::string Message) {
  size_t      pos;
  std::string nickName;

  pos = Message.find(' ');
  if (pos != std::string::npos) {
    nickName = Message.substr(0, pos);
    Message.erase(0, pos + 1);
  } else {
    throw std::runtime_error("No channel specified");
    return ;
  }
  std::cout << "Invite User " << nickName << " to " << Message << std::endl;
  // invite(nickName, Message);
}

void parseMode(std::string Message) {
  size_t      pos;
  std::string channelToChange, modesFlag;

  pos = Message.find(' ');
  if (pos != std::string::npos) {
    channelToChange = Message.substr(0, pos);
    Message.erase(0, pos + 1);
    pos = Message.find(' ');
    modesFlag = Message.substr(0, pos);
    if (pos == std::string::npos)
      Message.clear();
    else
      Message.erase(0, pos + 1);
  } else {
    throw std::runtime_error("No Mode specified");
    return ;
  }
  // mode(channelToChange, modesFlag, Message);
  std::cout << "Mode in " << channelToChange << " flag is " << modesFlag << " set to " << Message << std::endl;
}

void  executeCommands(std::string cmd, std::string Message) {
  if (cmd == "LOGIN") {
    std::cout << "Login into " << Message << std::endl;
    // logIn(Message);
  } else if (cmd == "NICK") {
    std::cout << "Nick change to " << Message << std::endl;
    // setNickName(Message);
  } else if (cmd == "USER") {
    std::cout << "User change to " << Message << std::endl;
    // setUserName(Message);
  } else if (cmd == "JOIN") {
    std::cout << "Join channel " << Message << std::endl;
    // joinChannel(Message);
  } else if (cmd == "OP") {
    std::cout << "OP " << Message << std::endl;
    // setOperator(Message);
  } else if (cmd == "PRVMSG") {
    parsePrvMsg(Message);
  } else if (cmd == "KICK") {
    parseKick(Message);
  } else if (cmd == "TOPIC") {
    parseTopic(Message);
  } else if (cmd == "MODE") {
    parseMode(Message);
  } else if (cmd == "INVITE") {
    parseInvite(Message);
  } else {
    throw(std::runtime_error("Command not found"));
  }
}

void extractCommand(std::string Message) {
  size_t      pos;
  std::string cmd;

  if (Message[0] == ':') {

  } else {
    pos = Message.find(' ');
    if (pos != std::string::npos) {
      cmd = Message.substr(0, pos);
      Message.erase(0, pos + 1);
    } else {
      cmd = Message;
      Message.clear();
    }
  }
  executeCommands(cmd, Message);
}


int parsing(std::string Message /*, Client &User*/) {
  try {
    extractCommand(Message);
  }
  catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}