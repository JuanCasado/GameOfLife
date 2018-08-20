#ifndef __GAME_OF_LIFE_HPP__
#define __GAME_OF_LIFE_HPP__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Grid.hpp"
#include "SideMenu.hpp"

class GameOfLife : public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();
private:
    virtual bool init();
    CREATE_FUNC(GameOfLife);
};

#endif // __GAME_OF_LIFE_HPP__
