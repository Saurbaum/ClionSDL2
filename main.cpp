#include <stdlib.h>
#include <SDL.h>
#include <chrono>
#include <iostream>

#define FRAME_RATE 60.0f

int main ( int argc, char** argv )
{
    SDL_version compiled;
    SDL_version linked;

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    printf("We compiled against SDL version %d.%d.%d ...\n",
            compiled.major, compiled.minor, compiled.patch);
    printf("But we are linking against SDL version %d.%d.%d.\n",
            linked.major, linked.minor, linked.patch);

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Window *sdlWindow;
    SDL_Renderer *sdlRenderer;
    SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &sdlWindow, &sdlRenderer);

    if ( !sdlWindow )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    // load an image
    SDL_Surface* bmp = SDL_LoadBMP("image.bmp");
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlRenderer, bmp);

    // centre the bitmap on screen
    SDL_Rect textureRect, displayRect;

    SDL_GetDisplayBounds(0, &displayRect);
    textureRect.x = (displayRect.w - bmp->w) / 2;
    textureRect.y = (displayRect.h - bmp->h) / 2;

    textureRect.w = bmp->w;
    textureRect.h = bmp->h;

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point lastUpdate = start;
    int updateCount = 0;

    // program main loop
    bool done = false;
    while (!done)
    {
        std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();

        float waitTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastUpdate).count();

        if (waitTime > 1000000/FRAME_RATE)
        {
            // message processing loop
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                // check for messages
                switch (event.type)
                {
                    // exit if the window is closed
                    case SDL_QUIT:
                        done = true;
                        break;

                        // check for key presses
                    case SDL_KEYDOWN:
                    {
                       // exit if ESCAPE is pressed
                       if (event.key.keysym.sym == SDLK_ESCAPE)
                            done = true;
                       break;
                    }

                    default:
                        break;
                } // end switch
            } // end of message processing

            // DRAWING STARTS HERE

            // clear screen
            SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
            SDL_RenderClear(sdlRenderer);

            SDL_RenderCopy(sdlRenderer, texture, NULL, &textureRect);

            // DRAWING ENDS HERE
            SDL_RenderPresent(sdlRenderer);

            lastUpdate = now;

            updateCount++;
        }
        else
        {
            if (waitTime - 1000000/FRAME_RATE > 12)
            {
                SDL_Delay(10);
            }
            else
            {
//                sleep(0);
            }
        }
    } // end main loop

    // free loaded bitmap
    SDL_FreeSurface(bmp);

    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();

    std::cout << "Total run time: " << std::chrono::duration_cast<std::chrono::seconds>(now - start).count() << " seconds" << std::endl;
    std::cout << "Update Count: " << updateCount << std::endl;

    std::cout << "Average Frame rate: " << (updateCount / (std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count()/1000.0f)) << std::endl;

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
