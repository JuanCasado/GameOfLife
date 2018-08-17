//
//  Menu.hpp
//  GameOfLife
//
//  Created by Juan Casado Ballesteros on 7/21/18.
//

#ifndef Menu_hpp
#define Menu_hpp
#include "cocos2d.h"
#include "Grid.hpp"
#include "ui/CocosGUI.h"

class SideMenu : public cocos2d::Scene{
public:
    static SideMenu * createSideMenu(Grid * grid);
private:
    SideMenu(Grid * grid);
    virtual bool init(void);
    cocos2d::Spawn * getSlideAction(void);
    cocos2d::Sprite * getBackground(void);
    Grid * grid;
    cocos2d::Vec2 * pausePos;
    void pauseClicked(void);
    cocos2d::Vec2 * largePos;
    void largeClicked(void);
    cocos2d::Vec2 * mediumePos;
    void mediumClicked(void);
    cocos2d::Vec2 * smallPos;
    void smallClicked(void);
    cocos2d::Label * pauseLabel;
    cocos2d::Sprite * background;
    cocos2d::Label * explanation;
    cocos2d::Sprite * largeBtt;
    cocos2d::Sprite * mediumBtt;
    cocos2d::Sprite * smallBtt;
};

#endif /* Menu_hpp */
