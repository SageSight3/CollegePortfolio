#include <semaphore.h>
using namespace std;

struct SharedRegion {
    char word[4000];
    sem_t remAccs; //number of remaining accesses to this region
};