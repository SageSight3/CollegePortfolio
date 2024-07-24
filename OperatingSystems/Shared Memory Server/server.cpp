#include <sys/shm.h>
#include <cstdio>
#include <semaphore.h>
#include <cstdlib>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include "SharedRegion.h"
using namespace std;

int main(int argc, char** argv) {
    //cout << argc % 3 << endl;
    if ((argc) % 3 != 1) {
        perror("Incorrect number of args given"); 
        exit(1);
    }
    //cout << "hi" << endl; //debug

    int fds[(argc-1)/3];
    int argvInd = 1;
    struct SharedRegion* regions[(argc-1)/3];

    for(int fd : fds) {
        fd = shm_open(argv[argvInd], O_CREAT | O_RDWR | O_TRUNC, 0644);
        if (fd == -1) {
            perror("fd failed for region " + argvInd % 3);
            exit(1);
        }
        
        if((ftruncate(fd,sizeof(struct SharedRegion)) + 1) == -1) {
            perror("ftruncate failed for region " + argvInd/3);
            exit(1);
        }

        //cout << "region truncated" << endl; //debug

        regions[(argvInd-1)/3] = (SharedRegion *)mmap(NULL, sizeof(struct SharedRegion), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (regions[(argvInd-1)/3] == MAP_FAILED) {
           perror("map failed for region " + argvInd % 3);
           exit(1);
        }
    
        //cout << "region mapped" << endl; //debug

        for (int index = 0; index < strlen(argv[argvInd+1]); ++index) {
            regions[(argvInd-1)/3]->word[index] = argv[argvInd+1][index];
        }

        //cout << "count for region " << (argvInd-1)/3 << " is " << argv[argvInd+2] << endl; //debug
        sem_init(&regions[(argvInd-1)/3]->remAccs, 1, atoi(argv[argvInd+2])); //error here?
        //cout << "count as number check: " << 5 + atoi(argv[argvInd+2]) << endl; //debug
        argvInd += 3;
    }

    //cout << "regions initialized" << endl; //debug

    bool regionsAlive[(argc-1)/3];
    for (bool region : regionsAlive) {
        region = true;
        //cout << "region alive? " << region << endl; //debug
    }

serverUp:
    //cout << endl; //spacing for debug
    sleep(1);

    argvInd = 1; //reset argvInd
    int remAccsInt;
    int *remAccsIntAddr = &remAccsInt; //sem_getvalue is dumb and requires the address to an ffing int
    for(int index = 0; index < (argc-1)/3; ++index) {

        //cout << "attempting to get remAccs on a region" << endl; //debug

        //cout << "region " << index << "'s word is " << regions[index]->word << endl; //debug
        //cout << "region " << index << "'s sem is " << regions[index]->word << endl; //debug

        int semValCheck = sem_getvalue(&regions[index]->remAccs, remAccsIntAddr);
        if (semValCheck == -1) {
            perror ("sem_getvalue failed");
        }

        //cout << "region " << index << "'s remAccs= " << remAccsInt << endl;
        
        if (remAccsInt == 0) {
            shm_unlink(argv[argvInd]);
            regionsAlive[index] = false;
        }

        argvInd += 3;
    }
    cout << endl;
    //cout << "attepting to check regionsAlive" << endl; //debug

    for (bool region : regionsAlive) {
        //cout << "region alive? " << region << endl; //debug
        //cout << "regionsAlive loop entered" << endl; //debug
        if (region) { 
            //cout << "test" << endl;
            //cout << region << endl; 
            //cout << "region alive" << endl; //debug
            goto serverUp; 
        }
        //cout << "Out of if\n"; //debug
    }

    cout << "server closed" << endl;
    exit(0);
}   
