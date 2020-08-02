#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(void){
    int pid = 0;
    FILE *pid_;
    pid_ = fopen("sound/status","w");

    pid = getpid();
    fprintf(pid_,"%d",pid);

    fclose(pid_);

    do{
        PlaySound("Blue (Da Ba Dee) - Eiffel 65.wav",NULL,SND_SYNC);
    }while(1==1);

    return 0;
}
