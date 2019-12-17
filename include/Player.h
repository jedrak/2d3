//
// Created by jedra on 20.10.2019.
//

#ifndef INC_2D_GAMES_EX1_PLAYER_H
#define INC_2D_GAMES_EX1_PLAYER_H


#include <SDL2/SDL_render.h>
#include "GameObject.h"

class Player : public GameObject{
    float speedX, speedY, accY;
public:
    float getSpeedX() const;

public:
    float getAccY() const;

public:
    void setAccY(float accY);

private:
    //SDL_Texture *playerTexture;
public:
    //SDL_Texture *getPlayerTexture() const;

    //void setPlayerTexture(SDL_Texture *playerTexture);

public:
    void setSpeedX(float speed);
    void setSpeedY(float speed);
    Player();
    Player(float x, float y);
    ~Player();
    //bool loadTexture(std::string path);
    void update();
    void start();

    Player(float x, float y, Shape s, float speedX, float speedY);

};


#endif //INC_2D_GAMES_EX1_PLAYER_H
