#include <iostream>		
#include <stdio.h>	
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <fcntl.h>




using namespace std;

const int BUFSIZE=102400;
int sock;
string sender;
string senderDomain;
//string receiverName;
//string receiverSMPT;
string receiver;
int lenWrite;
int lenRead;
char buf[BUFSIZE];

void ErrorCheck(bool condition, const char *msg)
{
	if (condition)
	{
		perror(msg);
		exit(1);
	}
}

int MakeSocket(const char *host, const char *port) {
	int s; 			
	int len;	
	struct sockaddr_in sa; 
	struct hostent *hp;
	struct servent *sp;
	int portnum;	
	int ret;

	hp = gethostbyname(host);
	ErrorCheck(hp==0, "Gethostbyname");
	bcopy((char *)hp->h_addr, (char *)&sa.sin_addr, hp->h_length);
	sa.sin_family = hp->h_addrtype;
	sscanf(port, "%d", &portnum);
	if (portnum > 0) {
		sa.sin_port = htons(portnum);
	}
	else {
		sp=getservbyname(port, "tcp");
		portnum = sp->s_port;
		sa.sin_port = sp->s_port;
	}
	s = socket(hp->h_addrtype, SOCK_STREAM, 0);
	ErrorCheck(s == -1, "Could not make socket");
	ret = connect(s, (struct sockaddr *)&sa, sizeof(sa));
	ErrorCheck(ret == -1, "Could not connect");
	return s;
}

void setSender(string address) {
    sender = address;
}


void setSenderDomain() { //isolates domain from sender's address
    int substrIndex = 0;
    for (int index = 0; index < sender.length(); ++index) { //finds index to substr sender from
        if (sender[index] == '@') {
            substrIndex = index;
            break;
        } 
    }

    //sets senderDomain to everything past the @ in sender
    senderDomain = sender.substr(substrIndex+1); 
}

/*
void setReceiverName(string name) {
    receiverName = name;
}

void setReceiverSMPT(string SMPT) {
    receiverSMPT = SMPT;
}

void setReceiver() {
    receiver = receiverName + "@" + receiverSMPT;
}
*/

void checkedWrite(string arg) { //write method with error check
    lenWrite = write(sock, arg.c_str(), arg.length());
    ErrorCheck(lenWrite == -1, "Write failed");
}

void checkedRead() { //read method with error check and console output
    lenRead = read(sock, buf, BUFSIZE - 1);
    ErrorCheck(lenRead == -1, "Read failed");
    buf[lenRead] = 0;
    cout << buf << endl;
}

//checked read use to verify response from server

void greetServer() { //tells server domain of sender
    checkedWrite("HELO " + senderDomain + "\r\n");
    checkedRead();
}

void establishSender() { //tells server sender address
    checkedWrite("MAIL FROM: " + sender + "\r\n");
    checkedRead();
}

void establishReceiver() { //tells server receiver address
    checkedWrite("RCPT TO: " + receiver + "\r\n");
    checkedRead();
    if (!(buf[0] == 2)) {
        cout << "Invalid address" << endl;
    }
}

void sendMessage() { //sends message with neccessary data
    checkedWrite("DATA\r\n");
    checkedRead();

    checkedWrite("To: " + receiver + "\r\n");
    checkedWrite("From: " + sender + "\r\n");

    string input;
    checkedWrite("Date: Thurs, 26 Jan 2024 02:36:04 -0800\r\n");

    cout << "What's the subject? " << endl;
    getline(cin, input);
    checkedWrite("Subject: " + input + "\r\n");

    cout << "Enter a message-ID: " << endl;
    getline(cin, input);
    checkedWrite("Message-ID: " + input + "\r\n");

    cout << "What do you want to say?" << endl;
    while (!(input == ".")) { //loop for message input
        getline(cin, input);
        checkedWrite(input + "\r\n");
    }
    checkedRead();
}

void quit() {
    checkedWrite("QUIT\r\n");
    checkedRead();
}

int main(int argc, char *argv[]) {
	char buf[BUFSIZE];

	// Make a socket
	sock = MakeSocket("mail.nmu.edu", "25");

	lenRead = read(sock, buf, BUFSIZE - 1);
	if(lenRead == -1) {
		perror("Read failed");
		exit(1);
	}
	buf[lenRead] = 0;
	cout << buf << endl;

    string input;
    while(!(input == "QUIT")) {

        //receiver address input
        cout << "What's the email address of who you're messaging " << endl;
        getline(cin, input);
        receiver = input; //receiver setter method does something different

        //sender address input
        cout << "What's your email address? " << endl;
        getline(cin, input);
        setSender(input);

        setSenderDomain();

        cout << senderDomain << endl;
        cout << sender << endl;
        cout << receiver << endl;

        greetServer();
        establishSender();
        establishReceiver();
        sendMessage();

        cout << "Type \"QUIT\" to end the program or press enter to send another message" << endl;
        getline(cin, input);
    }
    checkedWrite("QUIT\r\n");
    checkedRead();
    exit(0);    
}