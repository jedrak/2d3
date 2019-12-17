//
// Created by jedra on 17.12.2019.
//

#ifndef INC_2D_GAMES_EX1_LAYERS_H
#define INC_2D_GAMES_EX1_LAYERS_H


#include <vector>
#include "GameObject.h"

class Layers {


    std::vector<float> layerSpeed;

public:
    std::vector<std::vector<GameObject*>> layers;
    Layers();
    void addGOtoLayer(int, GameObject*);
    void update(float);
};


#endif //INC_2D_GAMES_EX1_LAYERS_H
