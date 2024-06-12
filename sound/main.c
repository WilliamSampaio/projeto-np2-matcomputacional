#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

int main()
{
    SDL_AudioSpec wav_spec;
    Uint32 wav_length;
    Uint8 *wav_buffer;

    /* Load the WAV */
    if (SDL_LoadWAV("Blue (Da Ba Dee) - Eiffel 65.wav", &wav_spec, &wav_buffer, &wav_length) == NULL)
    {
        fprintf(stderr, "Could not open test.wav: %s\n", SDL_GetError());
    }
    else
    {
        /* Do stuff with the WAV data, and then... */
        SDL_FreeWAV(wav_buffer);
    }

    return 0;
}
