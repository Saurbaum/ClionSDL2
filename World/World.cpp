//
// Created by ian on 26/12/15.
//

#include "World.h"

World::World(SDL_Renderer *sdlRenderer) {
    m_sdlRenderer = sdlRenderer;
}

void World::Render() {
    SDL_SetRenderDrawColor(m_sdlRenderer, 0, 0, 0, 255);
    SDL_RenderClear(m_sdlRenderer);
}