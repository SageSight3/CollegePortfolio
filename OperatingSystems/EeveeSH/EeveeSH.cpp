#include <unistd.h>
#include <cstdlib>
#include "readline/readline.h"
#include "readline/history.h"
#include <string>
#include <iostream>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <regex>
#include <fcntl.h>
#include <fstream>
#include <streambuf>
using namespace std;

void parentCmd(const char* cmd);

bool defaultPrompt = true;

char ** readyCommand(const char *cmd) {
    if (*cmd) { add_history(cmd); } //for arrow history
        
    //allows for ~ to be used in refernece to home directory
    regex home("~");
    string cmdString = regex_replace(cmd, home, getenv("HOME"));

    //split command into args
    char **args = new char*[10];
    int num = sscanf(cmdString.c_str(), "%ms %ms %ms %ms %ms %ms %ms %ms %ms %ms", &args[0], &args[1], &args[2], &args[3], &args[4], &args[5], &args[6], &args[7], &args[8], &args[9]);

    return args;
}

bool refinedExec(char ** readiedCommand) {
    string quit = "quit", ex = "exit";
    if (readiedCommand[0] == quit || readiedCommand[0] == ex) {
        exit(0);
    }

    string changeDir = "cd";
    if (readiedCommand[0] == changeDir) {
        if(chdir(readiedCommand[1]) == -1) {
            cout << "Directory doesn't exit" << endl;
            return true;
        }
    } else {
        //fork and exec
        int pid = fork();
        if (pid < 0) {
            perror("\033[1m\033[31mfork failed\033[0m");
            return false;
        }     
        if (pid == 0) {

            string reDirIn = "<", reDirOut = ">", reDirOutApp = ">>";
            bool inChanged = false, outChanged = false;
            int fdIn, fdOut;
            for (int index = 0; index < 10; ++index) {

                if ((readiedCommand[index] == "") || (readiedCommand[index] == nullptr)) { //null arg check
                    continue;
                }
                
                //dup2(fd, 0) changes exec arg input, dup2(fd, 1) changes output
                if ((readiedCommand[index] == reDirIn) || (readiedCommand[index] == reDirOut) || (readiedCommand[index] == reDirOutApp)) {
                    //not working, having issues with wsl bash also, how do?
                    if (readiedCommand[index] == reDirIn) {
                        //cout << "attempting to change in file" << endl; //debug
                        if (!inChanged) {
                            //cout << "in file is " << readiedCommand[index+1] << endl; //debug
                            fdIn = open(readiedCommand[index+1], O_RDONLY);
                            if (fdIn == -1) { 
                                perror("file input redirection failed"); 
                                exit(1);
                            }

                            if (dup2(fdIn, 0) == -1) {
                                perror("fdIn dup2 failed");
                                exit(1);
                            }
                            close(fdIn);
                            inChanged = true;
                        }

                    }

                    //working?
                    if (readiedCommand[index] == reDirOut) {
                        //cout << "attempting to change out file" << endl; //debug
                        if (!outChanged) {
                            //cout << "out file is " << readiedCommand[index+1] << endl; //debug
                            fdOut = open(readiedCommand[index+1], O_WRONLY | O_CREAT, 0644);
                            if (fdOut == -1) { 
                                perror("file output redirection failed"); 
                                exit(1);
                            }

                            if (dup2(fdOut, 1) == -1) {
                                perror("fdOut dup2 failed");
                                exit(1);
                            }
                            close(fdOut);
                            outChanged = true;
                        }
                    }

                    //working?
                    if(readiedCommand[index] == reDirOutApp) {
                        if (!outChanged) {
                            //cout << "out file is " << readiedCommand[index+1] << endl; //debug
                            fdOut = open(readiedCommand[index+1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                            if (fdOut == -1) { 
                                perror("file append output redirection failed"); 
                                exit(1);
                            }

                            if (dup2(fdOut, 1) == -1) {
                                perror("fdOutApp dup2 failed");
                                exit(1);
                            }
                            close(fdOut);
                            outChanged = true;
                        }
                    }
                    //remove redir op and file name from arg list
                    for (int shiftArg = index+2; shiftArg < 10; ++shiftArg) {
                        readiedCommand[shiftArg-2] = readiedCommand[shiftArg];
                    }
                }

                //cout << "arg " << index << " is " << readiedCommand[index] << endl; //debug
            }

            //cout << "attempting exec" << endl; //debug
            execvp(readiedCommand[0], readiedCommand);
            cout << "\033[1m\033[31mexec failed\033[0m" << endl; 
            return false;
        } else {
            int finishedExec = 9;
            int exitCode = 1;     
            while(finishedExec > 0) {
                finishedExec = waitpid(-1, &exitCode, WUNTRACED);
            }
        }
    }
    return true;
}

//interrupt handling //SIGINT is CTRL C, signal(SIGINT, <funcName>)
void signalCatcher(int signalNum) {
    cout << endl << getenv("PS1"); 
}

void setPrompt() {
    //ready prompt https://stackoverflow.com/questions/22753328/c-error-expression-must-have-integral-or-enum-type-getting-this-from-a-s
    string shellName = "\033[1m\033[34mEeveeSH\033[0m$ ";
    char pwd [1024];
    getcwd(pwd, 1024); //https://man7.org/linux/man-pages/man3/getcwd.3.html https://en.wikipedia.org/wiki/Pwd
    string pwdStr = pwd;
    string defaultPrompt = "PS1=\033[1m\033[35m" + pwdStr + "\033[0m:" + shellName;
    const char *ps1_ = defaultPrompt.c_str();
    //cout << ps1_ << endl; //debug
    char *ps1 = new char[strlen(ps1_)+1];
    strcpy(ps1, ps1_);
    putenv(ps1);
}

void execFromFile(char* fileName) {
    //cout << "attempting exec from file" << endl; //debug
    ifstream file;
    file.open(fileName, ios::binary);

    string cmdStr;
    while(getline(file, cmdStr)) {
        const char* cmd = cmdStr.c_str();
        //cout << "execFromFile command: " << cmdStr << endl; //debug
        parentCmd(cmd);
    }
    file.close();
}

void parentCmd(const char * cmd) {
    string cmdStr = cmd;
    //cout << "parentCmd was " << cmdStr << endl; //debug
    if (cmdStr == "") { return; }

    /*
    if (cmdStr.find("PS1=") != string::npos) {
        char *ps1 = new char[strlen(cmd)+1];
        strcpy(ps1, cmd);
         putenv(ps1);
         defaultPrompt = false;
        continue;
    }
    */

    if (cmdStr.find("=") != string::npos) {
        char *env = new char[strlen(cmd)+1];
        strcpy(env, cmd);
        putenv(env);
        if (cmdStr.find("PS1") != string::npos) { 
            defaultPrompt = false; 
        }
        return;
    }

    char** preppedCommand = readyCommand(cmd);
    /*
    for (int i = 0; i < 10; ++i) { //debug
        if (preppedCommand[i] == nullptr) { break; }
        cout << preppedCommand[i] << "<end of cmd>" << endl;
    }
    */
   
    string fileExec = ".";
    if (preppedCommand[0] == fileExec) { //for execing commands from file
        //cout << "am i here?" << endl;
        execFromFile(preppedCommand[1]);
        return;
    }

    if(!refinedExec(preppedCommand)) { //not working
        exit(1);
    }
}

int main(int argc, char** argv) {
    const char *cmd;

    //set up interrupt handler https://www.tutorialspoint.com/how-do-i-catch-a-ctrlplusc-event-in-cplusplus
    signal(SIGINT, signalCatcher);

    //set default prompt
    setPrompt();

    string launchScriptString = "umbreon.EeveeSH";
    const char* constLaunchScript = launchScriptString.c_str();
    char* launchScript = new char[strlen(constLaunchScript)+1];
    strcpy(launchScript, constLaunchScript);
    execFromFile(launchScript);
    
    while (((cmd = readline(getenv("PS1")))) != nullptr) { //color codes from https://stackoverflow.com/questions/9158150/colored-output-in-c
        parentCmd(cmd);
        if (defaultPrompt) { setPrompt(); } //not working, pwd is updating in shell though
        free((void*)cmd);
    }
}