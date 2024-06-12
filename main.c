#include <stdio.h> /* standard I/O routines                 */
#include <stdlib.h>
#include <pthread.h> /* pthread functions and data structures */
#include <SDL2/SDL.h>
#include <unistd.h>

#include "np2.h"
#include "np2txt.h"

/* function to be executed by the new thread */
// void *playSound(void *_wavFilename)
// {
//     printf("PlaySound!");

//     pthread_t tid;
//     tid = pthread_self();

//     sleep(3);
//     printf("playSound tid = (%lu)", tid);

//     SDL_Init(SDL_INIT_AUDIO);

//     // load WAV file
//     SDL_AudioSpec wavSpec;
//     Uint32 wavLength;
//     Uint8 *wavBuffer;

//     SDL_LoadWAV(_wavFilename, &wavSpec, &wavBuffer, &wavLength);

//     // open audio device
//     SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

//     // play audio
//     int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);

//     printf("Status: %d", success);

//     SDL_PauseAudioDevice(deviceId, 0);

//     // keep window open enough to hear the sound

//     SDL_Delay(1000 * 219);

//     // clean up

//     SDL_CloseAudioDevice(deviceId);
//     SDL_FreeWAV(wavBuffer);
//     SDL_Quit();
//     pthread_exit(NULL); /* terminate the thread */
// }

/* like any C program, program's execution begins in main */
int main(int argc, char *argv[])
{
    // int rc;                                               /* return value                           */
    // pthread_t thread_id;                                  /* thread's ID (just an integer)          */
    // char *wav = "sound/Blue (Da Ba Dee) - Eiffel 65.wav"; /* data passed to the new thread          */

    // /* create a new thread that will execute 'playSound' */
    // rc = pthread_create(&thread_id, NULL, playSound, (void *)wav);
    // if (rc) /* could not create thread */
    // {
    //     printf("\n ERROR: return code from pthread_create is %d \n", rc);
    //     // exit(1);
    // }

    // // char op;
    // // op = getchar();

    // // if (op == 'x')
    // // {
    // //     printf("Option: %c", op);
    // //     pthread_exit(NULL);
    // // }

    // while (1)
    // {
    //     printf("\n Created new thread (%lu) ... \n", thread_id);
    //     sleep(1);
    // }

    // // pthread_exit(NULL); /* terminate the thread */
    // printf(BRED "Hey this is the color red, and it's bold! \n" COLOR_RESET);
    // printf(RED "If" BLU "you" YEL "are" GRN "bored" CYN "do" MAG "this! \n" COLOR_RESET);
    // printf(BRED "If" BBLU "you" BYEL "are" BGRN "bored" BCYN "do" BMAG "this! \n" COLOR_RESET);
    // printf(URED "If" UBLU "you" UYEL "are" UGRN "bored" UCYN "do" UMAG "this! \n" COLOR_RESET);
    // txtTeam();
    // txtExit();
    // txtStarWarsRobos();

    // printf("%d", _confirmMessageBox("teste", "teste"));

    _startNP2();

    pthread_exit(NULL);
    return 0;
}
