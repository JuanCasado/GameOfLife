#include "GameOfLife.hpp"
#include "SimpleAudioEngine.h"
#include "Grid.hpp"
#include "SideMenu.hpp"

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
    this->addChild(sideMenu,2);
    this->addChild(grid,1);
    return true;
}
