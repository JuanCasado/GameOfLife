#include "GameOfLife.hpp"

USING_NS_CC;

Scene* GameOfLife::createScene(){
    return GameOfLife::create();
}

bool GameOfLife::init(){
    if (!Scene::init()){
        return false;
    }
    Grid *grid = Grid::createGrid();
    if (grid==nullptr){
        return false;
    }
    SideMenu *sideMenu = SideMenu::createSideMenu(grid);
    if (sideMenu==nullptr){
        return false;
    }
    auto screen = Director::getInstance()->getSafeAreaRect().size;
    auto button = ui::Button::create("il.png", "ih.png", "il.png");
    button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type){
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:{
                Application::getInstance()->openURL("http://www.mrblissfulgrin.com");
                break;
            }
            default:
                break;
        }
    });
    #if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
        auto btt = ui::Button::create("xbtt.png", "xbtt1.png", "xbtt.png");
        btt->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
            switch (type){
                case ui::Widget::TouchEventType::BEGAN:
                    break;
                case ui::Widget::TouchEventType::ENDED:{
                    Director::getInstance()->end();
                    break;
                }
                default:
                    break;
            }
        });
        btt->setPosition(Vec2(screen.width*0.95, screen.height*0.95));
        this->addChild(btt);
    #endif
    button->setPosition(Vec2(screen.width*0.90, screen.height*0.95));
    this->addChild(button);
    this->addChild(sideMenu,2);
    this->addChild(grid,1);
    return true;
}
