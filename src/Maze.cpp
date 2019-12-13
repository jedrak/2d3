//
// Created by jedra on 17.11.2019.
//

#include <ctime>
#include <iostream>
#include <stack>
#include "Maze.h"

Maze::Maze(float x, float y, const int width, const int height) : GameObject(x, y), width(width), height(height){
    nodes = new MazeNode*[width];
    for(int i = 0;  i < width; i++)
    {
        nodes[i] = new MazeNode[height];
        for(int j = 0; j < height; j++)
        {
            nodes[i][j].setX(this->getX()+i*30);
            nodes[i][j].setY(this->getY()+j*30);
        }
    }
}

void Maze::start() {

}

void Maze::update() {

}

void Maze::generate() {
    std::pair<int, int> current = std::make_pair(0, 0);
    std::stack<std::pair<int, int>> stack;
    nodes[current.first][current.second].setVisited(true);
    while(this->checkVisited()){
        //std::cout<< this->checkVisited()<<std::endl;
        std::pair<int, int> randomNeighbour;

        if(this->getUnvisitedNeighbours(current.first, current.second).size() > 0){
            randomNeighbour = this->getUnvisitedNeighbours(current.first, current.second)[rand()%this->getUnvisitedNeighbours(current.first, current.second).size()];
            //std::cout<<"current:"<< current.first<<" "<<current.second<<std::endl;
            //std::cout<<"neighbour:"<<randomNeighbour.first<<" "<<randomNeighbour.second<<std::endl;
            stack.push(current);
            deleteWallBetweenNodes(&nodes[current.first][current.second], &nodes[randomNeighbour.first][randomNeighbour.second]);
            current.first = randomNeighbour.first;
            current.second = randomNeighbour.second;
            nodes[current.first][current.second].setVisited(true);
        }
        else
        do
        {
            current.first = stack.top().first;
            current.second = stack.top().second;
            stack.pop();
        }while(!stack.empty() && this->getUnvisitedNeighbours(current.first, current.second).size() < 0);


//        for(int i = 0; i<width; i++){
//            for(int j = 0; j<height; j++){
//                std::cout<<nodes[i][j].isVisited();
//            }
//            std::cout<<std::endl;
//        }
    }
    int nrOfColls = 0;
    for(int i = 0;  i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
           nrOfColls += nodes[i][j].addColliders();
        }
    }
    std::cout<<nrOfColls<<std::endl;
    std::cout<<width*height<<std::endl;
}

void Maze::render(SDL_Renderer *rendere, int r, int g, int b, int a) {
    for(int i = 0;  i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            nodes[i][j].render(rendere, r, g, b, a);
        }
    }
}

bool Maze::checkVisited() {
    for(int i = 0; i<width; i++ ){
        for(int j = 0; j<height; j++){
            if(!nodes[i][j].isVisited()) return true;
        }
    }
    return false;
}



void Maze::deleteWallBetweenNodes(MazeNode* current, MazeNode* other) {
    float param;
    if(current->getX() == other->getX()){
        param = other->getY() - current->getY();
        if(param > 0){
            current->setWall(false, 1, 2);
            other->setWall(false, 1, 0);
        } else if( param < 0){
            current->setWall(false, 1, 0);
            other->setWall(false, 1, 2);
        }
    } else if(current->getY() == other->getY()) {
        param = other->getX() - current->getX();
        if (param > 0) {
            current->setWall(false, 2, 1);
            other->setWall(false, 0, 1);
        } else if (param < 0) {
            current->setWall(false, 0, 1);
            other->setWall(false, 2, 1);
        }
    }
}

int Maze::getRandomNeighbourX(int x) {
    std::vector<int> n;
    if(x > 0) n.push_back(x-1);
    if(x < width-1) n.push_back(x+1);
    int r = rand()%n.size();
    std::cout<<r<<std::endl;
    return n[r];
}

int Maze::getRandomNeighbourY(int y) {
    std::vector<int> n;
    if(y > 0) n.push_back(y-1);
    if(y < height-1) n.push_back(y+1);
    int r = rand()%n.size();
    std::cout<<r<<std::endl;
    return n[r];
}

std::vector<std::pair<int, int>> Maze::getUnvisitedNeighbours(int x, int y) {
    std::vector<std::pair<int, int>> buff;
    if(x > 0) {if(!nodes[x-1][y].isVisited()) buff.push_back(std::make_pair(x-1, y));}
    if(y > 0) {if(!nodes[x][y-1].isVisited()) buff.push_back(std::make_pair(x, y-1));}
    if(x < width-1 ){if(!nodes[x+1][y].isVisited()) buff.push_back(std::make_pair(x+1, y));}
    if(y < height-1) {if(!nodes[x][y+1].isVisited()) buff.push_back(std::make_pair(x, y+1));}
    return buff;
}

Maze::~Maze() {
    for(int i = 0 ; i<width; i++)
        delete(nodes[i]);
    delete(nodes);
}

MazeNode **Maze::getNodes() const {
    return nodes;
}

int Maze::getWidth() const {
    return width;
}

int Maze::getHeight() const {
    return height;
}
