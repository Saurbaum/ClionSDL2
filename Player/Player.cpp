//
// Created by ian on 26/12/15.
//

#include <SDL_surface.h>
#include <SDL_render.h>
#include "Player.h"

Player::Player(SDL_Renderer* sdlRenderer) : m_xPos(0), m_yPos(0), m_xVelocity(78.0f), m_yVelocity(42.0f) {
    m_sdlRenderer = sdlRenderer;
    LoadTexture("image.bmp");
}

Player::~Player() {
    // free loaded bitmap
    SDL_FreeSurface(m_surface);
}

void Player::Render() {
    SDL_RenderCopy(m_sdlRenderer, m_texture, NULL, &m_textureRect);
}

bool Player::LoadTexture(std::string textureFile) {
    m_surface = SDL_LoadBMP(textureFile.c_str());
    if (!m_surface)
    {
        return false;
    }

    m_texture = SDL_CreateTextureFromSurface(m_sdlRenderer, m_surface);

    // centre the player on screen
    SDL_Rect displayRect;

    SDL_GetDisplayBounds(0, &displayRect);

    m_xPos = displayRect.w / 2;
    m_yPos = displayRect.h / 2;

    UpdateTexturePos();

    m_textureRect.w = m_surface->w;
    m_textureRect.h = m_surface->h;

    return true;
}

void Player::Update(float updateInterval) {
    m_xPos += m_xVelocity * (updateInterval / 100000);
    m_yPos += m_yVelocity * (updateInterval / 100000);

    SDL_Rect displayRect;
    SDL_GetDisplayBounds(0, &displayRect);

    if (m_xPos >= displayRect.w - (m_surface->w / 2)){
        m_xPos = displayRect.w - (m_surface->w / 2);
        m_xVelocity *= -1;
    }

    if (m_xPos <= m_surface->w / 2){
        m_xPos = m_surface->w / 2;
        m_xVelocity *= -1;
    }

    if (m_yPos >= displayRect.h - (m_surface->h / 2)){
        m_yPos = displayRect.h - (m_surface->h / 2);
        m_yVelocity *= -1;
    }

    if (m_yPos <= m_surface->h / 2){
        m_yPos = m_surface->h / 2;
        m_yVelocity *= -1;
    }

    UpdateTexturePos();
}

void Player::UpdateTexturePos() {
    m_textureRect.x = static_cast<int>(m_xPos - (m_surface->w / 2));
    m_textureRect.y = static_cast<int>(m_yPos - (m_surface->h / 2));
}
