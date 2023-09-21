#include "Server.Class.hpp"
#include "Client.Class.hpp"

//server
int main(int argc, char **argv){

    (void) argc;
	int port = std::atoi(argv[1]); 
    Server server(port, "password");
    server.runServer();

    return (0);
}

// To test server open new terminal and enter:
// nc localhost 6667#include "Client.Class.hpp"

//parsing
// #include <iostream>
// #include <string>

// int parsing(std::string Message);

// int main() {
//   const char *correctOwnCmds[] = {"LOGIN phipno", "NICK phipno", "USER phipno", "JOIN channel1", "OP admin", "PRVMSG phipno Text is great jaja", NULL};
//   // const char *kickCmds[] = {"KICK channel1 phipno", "KICK channel1,channel2 phipno,phipno", "KICK channel1,channel2 phipno", "KICK channel1 phipno,admin,thisAndThat"};
//   const char *inviteCmds[] = {"INVITE phipno channel1", NULL};
//   const char *topicCmds[] = {"TOPIC channel1 texteverything and so on", NULL};
//   const char *ModeCmds[] = {"MODE channel1 -k", "MODE channel1 +o phipno", NULL};

//   parsing("LOGIN phipno");
//   parsing("PRVMSG phipno yes");
//   parsing("PRVMSG phipno hello sods dsd");

//   for (int i = 0; correctOwnCmds[i] != NULL; i++) {
//     parsing(correctOwnCmds[i]);
//   }
//   // for (int i = 0; kickCmds[i] != NULL; i++) {
//   //   parsing(kickCmds[i]);
//   // }
//   for (int i = 0; inviteCmds[i] != NULL; i++) {
//     parsing(inviteCmds[i]);
//   }
//   for (int i = 0; topicCmds[i] != NULL; i++) {
//     parsing(topicCmds[i]);
//   }
//   for (int i = 0; ModeCmds[i] != NULL; i++) {
//     parsing(ModeCmds[i]);
//   }
// }


//commands
// #include "Channel.Class.hpp"
// int main(void)
// {
// 	Channel chnl("test", false, false, "", -1);
// 	Client user1("User1", "Lee Roy");

// 	chnl.join("user1");
// 	chnl.join("user2");
// 	chnl.give_priveleges("user1");
// 	chnl.list_clients();
// 	chnl.kick("user2");
// 	chnl.list_clients();
// 	std::cout << chnl.get_topic() << std::endl;
// 	chnl.topic("Neu");
// 	std::cout << chnl.get_topic() << std::endl;
// 	chnl.list_channel_attributes();
// }