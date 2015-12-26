//
// Created by ian on 26/12/15.
//

#ifndef WORLD_H
#define WORLD_H


#include <SDL_render.h>

class World {
public:
    World(SDL_Renderer* sdlRenderer);
    ~World() { } ;

    virtual void Render();

private:
    SDL_Renderer* m_sdlRenderer;
};


#endif //WORLD_H
