#include <stdlib.h>
#include <SDL.h>
#include <chrono>
#include <iostream>
#include "Player/Player.h"
#include "World/World.h"
#include "StateController/StateController.h"

#define FRAME_RATE 60.0f

int main ( int argc, char** argv )
{
    for (auto i = 0; i < argc; ++i)
    {
        std::cout << "Arg " << i << ": " << argv[i] << std::endl;
    }

    SDL_version compiled;
    SDL_version linked;

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    std::cout << "We compiled against SDL version " << static_cast<int>(compiled.major) << "." << static_cast<int>(compiled.minor) << "." << static_cast<int>(compiled.patch) << std::endl;
    std::cout << "But we are linking against SDL version " << static_cast<int>(linked.major) << "." << static_cast<int>(linked.minor) << "." << static_cast<int>(linked.patch) << std::endl;

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout << "Unable to init SDL: " << SDL_GetError() << std::endl;
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
        std::cout << "Unable to set 640x480 video: " << SDL_GetError() << std::endl;
        return 1;
    }

    World world(sdlRenderer);
    StateController stateController;
    stateController.CreateMachine((IStateMachine *) new Player(sdlRenderer));

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

            stateController.Update(waitTime);

            // DRAWING STARTS HERE

            // clear screen
            world.Render();

            stateController.Render();

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
        }
    } // end main loop

    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();

    std::cout << "Total run time: " << std::chrono::duration_cast<std::chrono::seconds>(now - start).count() << " seconds" << std::endl;
    std::cout << "Update Count: " << updateCount << std::endl;

    std::cout << "Average Frame rate: " << (updateCount / (std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count()/1000.0f)) << std::endl;

    // all is well ;)
    std::cout << "Exited cleanly" << std::endl;
    return 0;
}
