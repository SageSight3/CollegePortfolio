/* WARNING!  THIS CODE DOES NOT WORK FOR REASONABLE YET LARGE  FILE SIZES!!!! */

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

int main(int argc, char *argv[]) {
	char buf[BUFSIZE];

	// Make a socket
	int sock = MakeSocket("euclid.nmu.edu", "1234");
	
	string nameComBase = "NAME";
	string nameCom = nameComBase;
	string name;
	cout << "What's your name? " << endl;
	getline(cin, name);
	name += "  ";
	nameCom += name;
	cout << nameCom << endl;

	int lenWrite;
	lenWrite = write(sock, nameCom.c_str(), nameCom.length());
	if (lenWrite == -1) {
		perror ("Failed to write");
		exit(1);
	}

	int lenRead;
	lenRead = read(sock, buf, BUFSIZE - 1);
	if(lenRead == -1) {
		perror("Read failed");
		exit(1);
	}
	buf[lenRead] = 0;
	cout << buf << endl;

	string input;
	while(lenRead > 0) {
		cout << "Send message: " << endl;
		getline(cin, input);

		//find and npos from https://cplusplus.com/reference/string/string/find/
		if(!(input.find("NAME") == string::npos)) { 
			input += "  ";
		}

		lenWrite = write(sock, input.c_str(), input.length());
		if (lenWrite == -1) {
			perror("loop write failed");
			exit(1);
		}
		//cout << "I sent " << input.c_str() << endl;


		lenRead = read(sock, buf, BUFSIZE-1);
		if (lenRead == -1) {
			perror("loop read failed");
			exit(1);
		}
		buf[lenRead] = 0;
		cout << buf << endl;

		if (input == "QUIT" || input == "quit") {
			cout << "leaving chat" << endl;
			exit(0);
		}
	}
	exit(1);
}
