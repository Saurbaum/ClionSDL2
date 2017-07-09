//
// Created by ian on 26/12/15.
//

#include "World.h"

World::World(SDL_Renderer *sdlRenderer) : m_increase(true), m_red(0), m_green(128), m_blue(0) {
    m_sdlRenderer = sdlRenderer;
}

void World::Render() {
    m_red = UpdateColour(m_red);
    m_green = UpdateColour(m_green);
    m_blue = UpdateColour(m_blue);

    SDL_SetRenderDrawColor(m_sdlRenderer, m_red, m_green, m_blue, 255);
    SDL_RenderClear(m_sdlRenderer);
}

Uint8 World::UpdateColour(Uint8 colour) {
    if (m_increase) {
        colour++;
    } else {
        colour--;
    }

    if (colour >= 255) {
        colour = 255;
        m_increase = false;
    }

    if (colour <= 0) {
        colour = 0;
        m_increase = true;
    }

    return colour;
}