/* My dumb server -- just an illustration */

#include <iostream>		// cout, cerr, etc
#include <stdio.h>		// perror
#include <string.h>		// bcopy
#include <netinet/in.h>		// struct sockaddr_in
#include <unistd.h>		// read, write, etc
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <assert.h>
#include <fstream>
#include <time.h>
#include <sys/wait.h>
#include <ext/stdio_filebuf.h>
#include <sys/file.h>
#include <arpa/inet.h>

using namespace std;

const int BUFSIZE=10240;

int MakeServerSocket(const char *port) {
	const int MAXNAMELEN = 255;
	const int BACKLOG = 3;	
	char localhostname[MAXNAMELEN]; // local host name
	int s; 		
	int len;
	struct sockaddr_in sa; 
	struct hostent *hp;
	struct servent *sp;
	int portnum;	
	int ret;


	hp = gethostbyname("localhost");

	sscanf(port, "%d", &portnum);
	if (portnum ==  0) {
		sp=getservbyname(port, "tcp");
		portnum = ntohs(sp->s_port);
	}
	sa.sin_port = htons(portnum);

	//bcopy((char *)hp->h_addr, (char *)&sa.sin_addr, hp->h_length);
	sa.sin_addr.s_addr = INADDR_ANY;
	sa.sin_family = hp->h_addrtype;

	s = socket(hp->h_addrtype, SOCK_STREAM, 0);

	ret = bind(s, (struct sockaddr *)&sa, sizeof(sa));
	if (ret < 0)
		perror("Bad");
	listen(s, BACKLOG);
	cout << "Waiting for connection on port " << port << endl;
	return s;
}

class UnknownException {
};

void checkedWrite(int fd, const char* data, int dataLen) {
	int len = write(fd, data, dataLen);
	if (len != dataLen) {
		throw UnknownException();
	}
}

string targetSubstr(string aString, string targetBeg, string targetEnd) {
	int adjustedTargetBeg = aString.find(targetBeg) + targetBeg.length();
	int length = aString.find(targetEnd) - adjustedTargetBeg;
	return aString.substr(adjustedTargetBeg, length);
}

int main(int argc, char *argv[]) {

	srand((unsigned) time(NULL)); //rng to create fork ids

	int s; 			// socket descriptor
	int len;		// length of reveived data
	char buf[BUFSIZE];	// buffer in which to read
	int ret;		// return code from various system calls


	s = MakeServerSocket(argv[1]);

	while (1) {

		int fd;
		string reqFileName;
		ifstream reqFile;
		char* page = nullptr;

		//log setup
		//ofstream logFile;
		string log = "";
		string hostName = "- ";
		string userAgent = "- ";
		string dateAndTime = "- ";
		string statusCode = "- ";
		string referer = "- ";
		string fileSize = "- ";
		string requestLine = "- ";

		struct sockaddr_in sa;
		int sa_len = sizeof(sa);
		fd = accept(s, (struct sockaddr *)&sa, (unsigned int *)&sa_len);
		int pid = fork();
		int id = rand();
		cout << id << " birthed with pid: " << pid << "\r\n" << endl;
		if (pid < 0) {
			cout << "Bad fork" << endl;
			exit(1);
		}
		if (pid == 0) {
			try {
				if (fd < 0) {
					throw UnknownException();
				}
				// Read a bit of data
				int len = read(fd, buf, BUFSIZE);
				if(len < 1) {
					throw UnknownException();
				}
				cout << "------------Read says:" << len << "--------\n";

				//requested file name retrieval
				int reqFileNameLen = 0; 
				int index = 5 ;
				while(!(buf[index] == ' ')) {
					++reqFileNameLen;
					++index;
				}
				for (int index = 0; index < reqFileNameLen; ++index) {
					reqFileName += buf[index + 5];
				}
				//cout << reqFileName << endl;
				//end of retrieval
				
				if(reqFileName == "throw") {
					cout << "throw requested" << endl;
					throw UnknownException();
					cout << "you shouldn't be here" << endl;
				}

				//client-side log info
				string bufToString;
				for (int index = 0; index < len; ++index) {
					bufToString += buf[index];
				}

				struct hostent* host;
				host = gethostbyaddr((const void*)&sa.sin_addr, sizeof(struct in_addr), AF_INET);
				string hostName = host->h_name;

				//hostName = targetSubstr(bufToString, "Host: ", "Connection: ");
				//hostName = hostName.substr(0, hostName.length() - 2) + " ";
				userAgent = targetSubstr(bufToString, "User-Agent", "AppleWebKit");
				userAgent = userAgent.substr(2, userAgent.length() - 3);

				time_t timeOfLog;
				struct tm * localTimeOfLog;
				time(&timeOfLog);
				localTimeOfLog = localtime(&timeOfLog);
				dateAndTime = asctime(localTimeOfLog);
				dateAndTime = dateAndTime.substr(0, dateAndTime.length() - 2);

				if (bufToString.find("Referer") != string::npos) {
					referer = targetSubstr(bufToString, "Referer: ", "Accept-Encoding: ");
					referer = "\"" + referer.substr(0, referer.length() - 2) + "\" ";
				}

				requestLine = bufToString.substr(0, bufToString.find("Host:") - 2);
				buf[len] = 0;
				cout << buf << endl;
				
				// Write to the web client

				string contentType;

				string reqFileTag;
				if (reqFileName.length() < 7) {
					reqFileTag = reqFileName;
				} else {
					reqFileTag = reqFileName.substr(reqFileName.length()-6, string::npos);
				}

				if (reqFileTag.find(".txt") != string::npos) {
					contentType = "text/plain";
				} else if (reqFileTag.find(".html") != string::npos || reqFileTag.find(".htm") != string::npos) {
					contentType = "text/html";
				} else if (reqFileTag.find(".jpg") != string::npos || reqFileTag.find(".jpeg") != string::npos) {
					contentType = "image/jpeg";
				} else if (reqFileTag.find(".gif") != string::npos) {
					contentType = "image/gif";
				} else {
					contentType = "application/octet-stream";
				}

				int reqFileSize;
				string header;
				reqFile.open(reqFileName, ios::binary);

				if(!reqFile.good()) {
					header = "HTTP/1.0 400 Error\r\ntext/plain\r\n";
					cout << header << endl;
					
					string error = "400s errorrrrr it wont workkkk wtfffffff";
					page = new char[error.length()];
					for (int index = 0; index < error.length(); ++index) {
						page[index] = error[index];
					}
					reqFileSize = error.length();
					statusCode = "400 "; //for log

				} else {
					reqFile.seekg(0, reqFile.end);
					reqFileSize = reqFile.tellg();
					reqFile.seekg(0, reqFile.beg);

					page = new char[reqFileSize];
				
					reqFile.read(page, reqFileSize);

					header = "HTTP/1.0 200 Great Day\r\n" + contentType + "\r\n";
					cout << header << endl;

					statusCode = "200 "; //for log
				}

				checkedWrite(fd, header.c_str(), header.length());
				checkedWrite(fd, "\r\n", 2);
				checkedWrite(fd, page, reqFileSize);

				//file size info and log record
				fileSize = to_string(reqFileSize) + " ";
				log = hostName + " [" + dateAndTime + "] " + "\"" + requestLine + "\" " + statusCode + fileSize + referer + "\"" + userAgent + "\"\r\n";
				//cout << log << endl;

				int logfd = fileno(::fopen("log.log", "a"));
   				__gnu_cxx::stdio_filebuf<char> filebuf(logfd, std::ios::out);
				cout << "Locking log\r\n" << endl;
				flock(logfd, 2); 
				ostream file(&filebuf);
				file.seekp(0, ios::end);
				cout << "writing to log\r\n" << endl;
				file.write(log.c_str(), log.length());
				sleep(5);
				cout << "Unlocking log\r\n" << endl;
				flock(logfd, 8);


			} catch (UnknownException anException) {
				cout << "Exception thrown" << endl;
			}

			close(fd);
			if (page) { delete[] page; }
			reqFile.close();
			//logFile.close();
			cout << "killing " << id << "\r\n" << endl;
			exit(0);
		}
		if (pid > 0) {
			close(fd);
			int exitCode = 1;
			int zombie = 999;
			while (zombie > 0) {
				zombie = waitpid(-1, &exitCode, WNOHANG);
				cout << "Zombie: " << zombie << " harvested" << endl;
				cout << "Exit code: " << exitCode << endl;
				cout << endl;
			}	
		}
	}
}


