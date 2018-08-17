//
//  Grid.hpp
//  GameOfLife
//
//  Created by Juan Casado Ballesteros on 7/21/18.
//

#ifndef Grid_hpp
#define Grid_hpp
#include "cocos2d.h"
#include "Cell.hpp"
#include <vector>

class Grid : public cocos2d::Scene{
public:
    enum gridSize{Large, Medium, Small};
    static Grid * createGrid(gridSize size=Medium, int line_width=1, int margin=10);
    void setGridSize(Grid::gridSize size);
    void changeState();
    bool getState();
    Grid::gridSize getSize(void);
    void setVel(int vel);
private:
    Grid (int line_width, int margin);
    Grid (int rows, int cols, int line_width, int margin);
    virtual bool init(Grid::gridSize size);
    int rows;
    int cols;
    int line_width;
    int margin;
    bool pause;
    Grid::gridSize size;
    cocos2d::Spawn * getFadeAction (void);
    cocos2d::Sprite *img;
    std::vector <cocos2d::Sprite*> lines;
    std::vector <std::vector<Cell*>> cells;
    void nextFrame(float t);
    float speed;
};

#endif /* Grid_hpp */
