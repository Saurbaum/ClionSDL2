//
// Created by ian on 26/12/15.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>
#include "../Interface/IStateMachine.h"

class Player : public IStateMachine {
public:
    explicit Player(SDL_Renderer* sdlRenderer);
    ~Player();

    void Render() override;

    void Update(float updateInterval) override;

private:
    SDL_Surface* m_surface;
    SDL_Texture* m_texture;

    SDL_Renderer* m_sdlRenderer;

    SDL_Rect m_textureRect;

    float m_xPos;
    float m_yPos;

    float m_xVelocity;
    float m_yVelocity;

    bool LoadTexture(std::string textureFile);
    void UpdateTexturePos();
};


#endif //PLAYER_H
