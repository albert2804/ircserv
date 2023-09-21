#include "Server.Class.hpp"
#include "Client.Class.hpp"
#include "Channel.Class.hpp"

/* Commands for all users*/


// PASS
// first step, even before connecting with a nickname
// entry from client: PASS YourServerPassword
// variables in t_msg struct:
//      message.command = PASS
//      message.paramVec[0] = YourServerPassword

    //    462    ERR_ALREADYREGISTRED
    //           ":Unauthorized command (already registered)"

    //      - Returned by the server to any link which tries to
    //        change part of the registered details (such as
    //        password or user details from second USER message).

        //    461    ERR_NEEDMOREPARAMS
        //       "<command> :Not enough parameters"

        //  - Returned by the server by numerous commands to
        //    indicate to the client that it didn't supply enough
        //    parameters.

int Server::pass(t_msg *message, Client client){
    if (client.getRegistrationStatus() == true)
        numReply(462, message, client);
    else if (message->paramVec[0].empty())
        numReply(461, message, client);
    else if (message->paramVec[0].compare(this->_password) == 0){
        client.registerClient(true);
        return 0;
    }
    return 1;
}

// NICK
// NICK <your-nick>
// when connecting for the first time, choose a nickname

        //    ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
        //    ERR_NICKNAMEINUSE               ERR_NICKCOLLISION
        //    ERR_UNAVAILRESOURCE             ERR_RESTRICTED

    //    431    ERR_NONICKNAMEGIVEN
    //           ":No nickname given"

    //      - Returned when a nickname parameter expected for a
    //        command and isn't found.

    //    432    ERR_ERRONEUSNICKNAME
    //           "<nick> :Erroneous nickname"

    //      - Returned after receiving a NICK message which contains
    //        characters which do not fall in the defined set.  See
    //        section 2.3.1 for details on valid nicknames.

    //    433    ERR_NICKNAMEINUSE
    //           "<nick> :Nickname is already in use"

    //      - Returned when a NICK message is processed that results
    //        in an attempt to change to a currently existing
    //        nickname.

    //        436    ERR_NICKCOLLISION
    //           "<nick> :Nickname collision KILL from <user>@<host>"

    //      - Returned by a server to a client when it detects a
    //        nickname collision (registered of a NICK that
    //        already exists by another server).

    //    437    ERR_UNAVAILRESOURCE
    //           "<nick/channel> :Nick/channel is temporarily unavailable"

    //      - Returned by a server to a user trying to join a channel
    //        currently blocked by the channel delay mechanism.

    //      - Returned by a server to a user trying to change nickname
    //        when the desired nickname is blocked by the nick delay
    //        mechanism.

    //    484    ERR_RESTRICTED
    //       ":Your connection is restricted!"

    //      - Sent by the server to a user upon connection to indicate
    //      the restricted nature of the connection (user mode "+r").



// USER
// USER <your-username> <your-hostname> <your-servername> :<your-realname>
// ex:
// USER MyUsername MyHostname MyServername :John Doe

// JOIN
// JOIN #channelname

// PRIVMSG
// PRIVMSEG <msgtarget> <text to be sent>



// 001    RPL_WELCOME
//               "Welcome to the Internet Relay Network
//                <nick>!<user>@<host>"
//        002    RPL_YOURHOST
//               "Your host is <servername>, running version <ver>"
//        003    RPL_CREATED
//               "This server was created <date>"
//        004    RPL_MYINFO
//               "<servername> <version> <available user modes>
//                <available channel modes>"

//          - The server sends Replies 001 to 004 to a user upon
//            successful registration.


/* --------------------------------------------------------------------------------------*/

/*Commands specific to channel operators*/







