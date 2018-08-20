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
    auto screen = Director::getInstance()->getSafeAreaRect().size;
    button->setPosition(Vec2(screen.width*0.95, screen.height*0.95));
    this->addChild(button);
    this->addChild(sideMenu,2);
    this->addChild(grid,1);
    return true;
}
