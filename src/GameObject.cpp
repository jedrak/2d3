//
// Created by jedra on 08.10.2019.
//

#include "GameObject.h"

#include <utility>
void drawEquilateralTriangle(SDL_Renderer *renderer, int x, int y, int a, int h, int r, int g, int b, int alpha) {
    if(h>0) {
        SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
        int pointsX[] = {
                x, x - (a / 2), x + (a / 2)
        };

        int pointsY[] = {
                y - (2 * (h / 3)), y + (h / 3), y + (h / 3)
        };
        for(int i = 0; i<(pointsX[2]-pointsX[1]); i++){
            SDL_RenderDrawLine(renderer, pointsX[0], pointsY[0], pointsX[1]+i, pointsY[1]);
        }
    }
}

GameObject::GameObject(float x, float y) : x(x), y(y), shape(Shape::rect){}

GameObject::GameObject() : x(0), y(0), shape(Shape::rect){}

float GameObject::getX() const {
    return x;
}

float GameObject::getY() const {
    return y;
}

void GameObject::setY(float y) {
    GameObject::y = y;
}

void GameObject::setX(float x) {
    GameObject::x = x;
}

void GameObject::render(SDL_Renderer *renderer, int r, int g, int b, int a) {
    if(this->shape == Shape::rect) {
        SDL_Rect fillRect = {this->getX(), this->getY(), 10, 10};
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        SDL_RenderFillRect(renderer, &fillRect);
    }
    else if(this->shape == Shape::circle){}
    else if(this->shape == Shape::triangle){
        drawEquilateralTriangle(renderer, this->x, this->y, 10, 11, r, g, b, a);
    }
    else if(this->shape == Shape::texture){}
}

GameObject::GameObject(float x, float y, Shape s) : x(x), y(y), shape(s){}

Shape GameObject::getShape() const {
    return shape;
}


GameObject::~GameObject() = default;

