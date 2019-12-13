//
// Created by jedra on 18.11.2019.
//

#ifndef INC_2D_GAMES_EX1_COLLIDER_H
#define INC_2D_GAMES_EX1_COLLIDER_H


#include "GameObject.h"

class Collider : public GameObject{
private:
    bool kinematic;
    GameObject* parent;
    float w, h;
public:
    float getW() const;

    void setW(float w);

    float getH() const;

    void setH(float h);

public:
    Collider(float x, float y, Shape s, bool kinematic, GameObject *parent, float w, float h);

    bool checkCollision(Collider* other);
    void update() override;
    void start() override;

};


#endif //INC_2D_GAMES_EX1_COLLIDER_H
