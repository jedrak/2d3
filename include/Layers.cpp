//
// Created by jedra on 17.12.2019.
//
#define LEVEL_WIDTH 1080
#include "Layers.h"

Layers::Layers() {
    layerSpeed = std::vector<float>({-.5, -4, -.3});
    layers = std::vector<std::vector<GameObject*>>(3);
    for(std::vector<GameObject*> v : layers){
        v = std::vector<GameObject*>();
    }
}

void Layers::addGOtoLayer(int whichLayer, GameObject* go) {
    layers[whichLayer].push_back(go);
}

void Layers::update(float playerspeed) {
    int layer = 0;

    for (std::vector<GameObject *> v : layers) {
        for (int i = 0; i < v.size(); i++) {
            v[i]->setX(v[i]->getX() + layerSpeed[layer] * playerspeed);
            if(v[i]->getX()<(-LEVEL_WIDTH/2.0)) v[i]->setX((LEVEL_WIDTH));
        }
        layer++;
    }

}
