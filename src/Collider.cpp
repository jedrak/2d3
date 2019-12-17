//
// Created by jedra on 18.11.2019.
//

#include <iostream>
#include "Collider.h"

void Collider::update() {
    this->setX(this->parent->getX());
    this->setY(this->parent->getY());

}

void Collider::start() {
    this->setX(this->parent->getX());
    this->setY(this->parent->getY());
}

bool Collider::checkCollision(Collider* other) {
    switch(this->getShape()){

        case rect:
            if(other->getShape() == Shape::rect){
                float   r1 = this->getX()+w, r2 = other->getX()+other->getW(),
                        l1 = this->getX(), l2 = other->getX(),
                        t1 = this->getY(), t2 = other->getY(),
                        b1 = this->getY()+h, b2 = other->getY()+other->getH();
                //std::cout<<(r1>l2) << (r2>l1) << (b1>t2) << (b2>t1) <<std::endl;
                if(r1>l2 && r2>l1 && b1>t2 && b2>t1) {
                    float left = r2 - l1, right = r1 - l2, top = b2 - t1, bottom = b1 - t2, deltaX = 0, deltaY = 0;
                    if(this->getY()<other->getY()) {
                        deltaY = -bottom;
                    }
                    else{
                        deltaY = +top;
                    }

                    if(this->getX()<other->getX()) {
                        deltaX = -right;
                    }
                    else{
                        deltaX = +left;
                    }
                    if(abs(deltaX) < abs(deltaY)) deltaY = 0;
                    else if(abs(deltaX) > abs(deltaY)) deltaX = 0;
                    //std::cout<<"left: " << left << " right: "<< right << " top: "<< top << " bottom: " << bottom<<std::endl;
                    //std::cout << "x: " << this->getX() << " y: " << this->getY() << " deltaX: " << deltaX << " deltaY: " << deltaY << std::endl;
                    this->parent->setX(this->parent->getX()+deltaX);
                    this->parent->setY(this->parent->getY()+deltaY);
                }
                return r1>l2 && r2>l1 && b1>t2 && b2>t1;
            }
            break;
        case triangle:
            break;
        case circle:
            break;
        case 4:
            break;
    }
}

Collider::Collider(float x, float y, Shape s, bool kinematic, GameObject *parent, float w, float h)
        : GameObject(x, y, s), kinematic(kinematic), parent(parent), w(w), h(h) {}

float Collider::getW() const {
    return w;
}

void Collider::setW(float w) {
    Collider::w = w;
}

float Collider::getH() const {
    return h;
}

void Collider::setH(float h) {
    Collider::h = h;
}
