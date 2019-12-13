//
// Created by jedra on 08.10.2019.
//

#ifndef INC_2D_GAMES_EX1_GAMEOBJECT_H
#define INC_2D_GAMES_EX1_GAMEOBJECT_H


#include <string>
#include <SDL2/SDL_render.h>

enum Shape{
    rect,
    triangle,
    circle,
    texture
};

class GameObject {
private:
    float  x, y;
    Shape shape;
public:
    GameObject();
    GameObject(float x, float y);
    GameObject(float x, float y, Shape s);
    ~GameObject();
    virtual void update() = 0;
    virtual void start() = 0;

    Shape getShape() const;

    float getX() const;
    void setX(float x);
    float getY() const;
    void setY(float y);

    virtual void render(SDL_Renderer *renderer, int r, int g, int b, int a);
};


#endif //INC_2D_GAMES_EX1_GAMEOBJECT_H
