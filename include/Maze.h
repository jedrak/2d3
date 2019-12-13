//
// Created by jedra on 17.11.2019.
//

#ifndef INC_2D_GAMES_EX1_MAZE_H
#define INC_2D_GAMES_EX1_MAZE_H


#include <vector>
#include "GameObject.h"
#include "MazeNode.h"

class Maze : public GameObject {
private:


    int width, height;
    MazeNode** nodes;
public:

    Maze(float x, float y, int width, int height);
    ~Maze();
    void start();

    int getWidth() const;

    int getHeight() const;

    MazeNode **getNodes() const;

    void update() override;
    bool checkVisited();
    int getRandomNeighbourX(int x);
    int getRandomNeighbourY(int y);
    std::vector<std::pair<int, int>> getUnvisitedNeighbours(int x, int y);
    void deleteWallBetweenNodes(MazeNode* current, MazeNode* other);
    void generate();
    void render(SDL_Renderer* rendere, int r, int g, int b, int a);
};


#endif //INC_2D_GAMES_EX1_MAZE_H
