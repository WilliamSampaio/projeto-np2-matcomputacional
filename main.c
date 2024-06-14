#include <pthread.h> /* pthread functions and data structures */

#include "np2.h"

int main(int argc, char *argv[])
{
    _startNP2();
    pthread_exit(NULL);
    return 0;
}
