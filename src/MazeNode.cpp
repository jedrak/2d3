//
// Created by jedra on 17.11.2019.
//

#include <iostream>
#include "MazeNode.h"



MazeNode::MazeNode(float x, float y) : GameObject(x, y), visited(false){
    for(int i =0; i < 3; i++) {
        for(int j = 0; j < 3; j++){
            this->walls[i][j] = i != 1 || j != 1;
        }
    }
}

bool MazeNode::hasWall(int x, int y) const {
    return this->walls[x][y];
}

void MazeNode::setWall(bool value, int x, int y) {
    this->walls[x][y] = value;
}

void MazeNode::render(SDL_Renderer *renderer, int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    for(int i =0; i < 3; i++) {
        for(int j = 0; j < 3; j++){
            if(walls[i][j]) {
                SDL_Rect fillRect = {this->getX()+i*15, this->getY()+j*15, 10, 10};
                SDL_RenderFillRect(renderer, &fillRect);


            }
        }
    }
}



void MazeNode::update() {

}

void MazeNode::start() {

}

MazeNode::MazeNode() : GameObject(), visited(false){
    for(int i =0; i < 3; i++) {
        for(int j = 0; j < 3; j++){
            this->walls[i][j] = i != 1 || j != 1;
        }
    }
}

bool MazeNode::isVisited() const {
    return visited;
}

void MazeNode::setVisited(bool visited) {
    MazeNode::visited = visited;
}

int MazeNode::addColliders() {
    for(int i =0; i < 3; i++) {
        for(int j = 0; j < 3; j++){
            if(walls[i][j]) {
                SDL_Rect fillRect = {this->getX()+i*15, this->getY()+j*15, 10, 10};
                colls.push_back(new Collider(fillRect.x-fillRect.w/2, fillRect.y+fillRect.h/2, Shape::rect, false, this, 5, 5));
                //std::cout<<" x "<<colls.back()->getX()<<" y "<<colls.back()->getY()<<std::endl;
            }else{
                //std::cout<<"tu nic nie ma "<<this->getX()+i*15<<" "<<this->getY()+j*15<<std::endl;
            }
        }
    }

    return colls.size();
}
