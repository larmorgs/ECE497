/*
 *   main.c
 *
 * ============================================================================
 * Copyright (c) Texas Instruments Inc 2005
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied or provided.
 * ============================================================================
 */

// Standard Linux headers
#include     <stdio.h>              // Always include this header
#include     <stdlib.h>             // Always include this header
#include     <signal.h>             // Defines signal-handling functions (i.e. trap Ctrl-C)
#include     <unistd.h>
#include     <curses.h>

// Application headers
#include     "debug.h"
#include     "thread.h"
#include     "video_thread.h"
#include     "audio_thread.h"

/* Global thread environments */
video_thread_env video_env = {0, 0};
audio_thread_env audio_env = {0, 0};

/* Store previous signal handler and call it */
void (*pSigPrev)(int sig);

/* Callback called when SIGINT is sent to the process (Ctrl-C) */
void signal_handler(int sig)
{
    DBG( "Ctrl-C pressed, cleaning up and exiting..\n" );

    video_env.quit = 1;
    #ifdef _DEBUG_
        sleep(1);
    #endif

    audio_env.quit = 1;

    if( pSigPrev != NULL )
        (*pSigPrev)( sig );

}

WINDOW *w;

//*****************************************************************************
//*  main
//*****************************************************************************
int main(int argc, char *argv[])
{
/* The levels of initialization for initMask */
#define VIDEOTHREADATTRSCREATED 0x1
#define VIDEOTHREADCREATED      0x2
#define AUDIOTHREADATTRSCREATED 0x4
#define AUDIOTHREADCREATED      0x8
    unsigned int    initMask  = 0;
    int             status    = EXIT_SUCCESS;

    pthread_t audioThread, videoThread;
    void *audioThreadReturn, *videoThreadReturn;

    /* Set the signal callback for Ctrl-C */
    pSigPrev = signal( SIGINT, signal_handler );

    w = initscr();
    if (w == NULL) {
        ERR("ncurses init failed\n");
        status = EXIT_FAILURE;
        goto cleanup;
    }
    cbreak();
    nodelay(w, TRUE);
    noecho();

    /* Make video frame buffer visible */
    system("cd ..; ./vid1Show");

    /* Create a thread for video */
    DBG( "Creating video thread\n" );
    printf( "\tPress Ctrl-C to exit\n" );

    if(launch_pthread(&videoThread, 0, 0, video_thread_fxn, &video_env) != thread_SUCCESS){
        ERR("pthread create failed for video thread\n");
        status = EXIT_FAILURE;
        goto cleanup;
    }
    initMask |= VIDEOTHREADCREATED;
    
    #ifdef _DEBUG_
        sleep(1);
    #endif

    /* Create a thread for audio */
    DBG( "Creating audio thread\n" );
    printf( "\tPress Ctrl-C to exit\n" );

    if(launch_pthread(&audioThread, 0, 0, audio_thread_fxn, &audio_env) != thread_SUCCESS){
        ERR("pthread create failed for video thread\n");
        status = EXIT_FAILURE;
        goto cleanup;
    }
    initMask |= AUDIOTHREADCREATED;

    int count = 0;

    while (video_env.quit == 0 && audio_env.quit == 0) {
        if (getch() == 32) {
            count = 0;
            video_env.replay = 1;
            audio_env.replay = 1;
            system("cd ..; ./resetVideo");
            system("cd ..; ./vid2Show");
        }
        if (count++ == 5 && audio_env.replay == 1) {
            video_env.replay = 0;
            audio_env.replay = 0;
            system("cd ..; ./resetVideo");
            system("cd ..; ./vid1Show");
        }
        sleep(1);
    }


cleanup:
    if (initMask & AUDIOTHREADCREATED) {
        pthread_join(audioThread, (void **) &audioThreadReturn);
    }
    if (initMask & VIDEOTHREADCREATED) {
        pthread_join(videoThread, (void **) &videoThreadReturn);
    }

    if (w != NULL) {
        delwin(w);
        endwin();
        refresh();
    }

    /* Make video frame buffer invisible */
    system("cd ..; ./resetVideo");

    exit( status );
}
