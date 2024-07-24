#include <sys/shm.h>
#include <cstdio>
#include <semaphore.h>
#include <cstdlib>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <time.h>
#include "SharedRegion.h"
using namespace std;

int main (int argc, char** argv) {
    if (argc != 2) { 
        perror("no shmpath given");
        exit(1);
    }

    int fd = shm_open(argv[1], O_RDWR, 0);
    if (fd == -1) {
        perror("shm_open failed");
        exit(1);
    }

    struct SharedRegion* access = (SharedRegion*)mmap(nullptr, sizeof(struct SharedRegion), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (access == MAP_FAILED) {
        perror("mmap of access failed");
        exit(1);
    }

    int waitCheck;
    struct timespec waitInterval;
    if (clock_gettime(CLOCK_MONOTONIC, &waitInterval) == -1) {
        perror("gettime failed");
        exit(1);
    }

    waitInterval.tv_sec += 1;
    if ((waitCheck = sem_timedwait(&access->remAccs, &waitInterval)) == -1) {
        perror("wait failed");
        exit(1);
    }

    cout << access->word << endl;
    exit(0);
}