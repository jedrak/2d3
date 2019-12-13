//
// Created by jedra on 17.11.2019.
//

#ifndef INC_2D_GAMES_EX1_MAZENODE_H
#define INC_2D_GAMES_EX1_MAZENODE_H


#include <vector>
#include "GameObject.h"
#include "Collider.h"

class MazeNode : public GameObject {
private:
     bool walls[3][3];
     bool visited;

public:
    std::vector<Collider*> colls;
    bool isVisited() const;

    void setVisited(bool visited);

public:
    MazeNode(float x, float y);

    MazeNode();

    bool hasWall(int x, int y) const;
    void setWall(bool, int, int);
    void render(SDL_Renderer*, int, int, int, int) override;
    void start() override;
    void update();
    int addColliders();
};


#endif //INC_2D_GAMES_EX1_MAZENODE_H
