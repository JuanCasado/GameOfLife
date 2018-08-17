//
//  Cell.hpp
//  GameOfLife
//
//  Created by Juan Casado Ballesteros on 7/23/18.
//

#ifndef Cell_hpp
#define Cell_hpp
#include "cocos2d.h"

class Cell : public cocos2d::Sprite{
public:
    static Cell * createCell(cocos2d::Vec2 pos, cocos2d::Size size, bool paused, cocos2d::Texture2D *img);
    bool isAlive(void);
    bool isPaused(void);
    void setAlive(bool state);
    void resetNeighbours(void);
    int getNeighbours(void);
    void addNeighbour(void);
    void setPaused(bool state);
    void newColor(void);
    ~Cell();
private:
    Cell(bool paused);
    int neighbours;
    bool alive;
    bool paused;
    void onTouched(void);
    void addEvents();
    cocos2d::EventListenerTouchOneByOne * listener;
};

#endif /* Cell_hpp */
