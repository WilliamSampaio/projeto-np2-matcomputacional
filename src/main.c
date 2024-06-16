#include <pthread.h>

#include "np2.h"

int main(int argc, char *argv[])
{
    _start_();
    pthread_exit(NULL);
    return 0;
}
