//
//  Grid.cpp
//  GameOfLife
//
//  Created by Juan Casado Ballesteros on 7/20/18.
//

#include "Grid.hpp"

USING_NS_CC;

Grid * Grid::createGrid(Grid::gridSize size, int line_width, int margin){
    Grid * grid = new Grid(line_width, margin);
    if (grid && grid->init(size)){
        grid->autorelease();
        return grid;
    }else{
        delete grid;
        grid = nullptr;
        return nullptr;
    }
}

Grid::Grid(int line_width, int margin){
    this->line_width = line_width;
    this->margin = margin;
    this->pause = false;
    this->speed = 0.7;
}

bool Grid::init(Grid::gridSize size){
    if (!Scene::init()){
        return false;
    }
    img = Sprite::create("WhiteRect.png");
    if (img ==nullptr){
        delete img;
        return false;
    }
    setGridSize(size);
    this->schedule(schedule_selector(Grid::nextFrame), 0.7);
    return true;
}

Spawn * Grid::getFadeAction(){
    Vector<FiniteTimeAction*> actions;
    actions.pushBack(FadeTo::create(1, 255));
    actions.pushBack(TintTo::create(3, 0, 0, 0));
    return Spawn::create(actions);
}

void Grid::changeState(){
    this->pause = !this->pause;
    if(this->pause){
        this->unschedule(schedule_selector(Grid::nextFrame));
    }else{
        this->schedule(schedule_selector(Grid::nextFrame), speed);
    }
    for (auto cell:cells){
        for (auto cel : cell){
            cel->setPaused(pause);
        }
    }
}

void Grid::setGridSize(Grid::gridSize size){
    this->size = size;
    switch (size) {
        case Large:
            rows = 22;
            cols = 22;
            break;
        case Medium:
            rows = 16;
            cols = 16;
            break;
        case Small:
            rows = 10;
            cols = 10;
            break;
        default:
            rows = 1;
            cols = 1;
            break;
    }
    for (auto line:lines){
        this->removeChild(line);
    }
    lines.clear();
    img = Sprite::create("WhiteRect.png");
    auto screen = Director::getInstance()->getSafeAreaRect().size;
    float rows_step = (screen.height-line_width-margin*2)/(rows);
    float cols_step = (screen.height-line_width-margin*2)/(cols);
    for (int x = 0; x < rows+1; x++){
        auto line = Sprite::createWithTexture(img->getTexture());
        line->setAnchorPoint(Vec2(0, 0));
        line->setContentSize(Size(screen.height-margin*2, line_width));
        line->setPosition(Vec2(margin, margin+x*rows_step));
        line->setOpacity(0);
        this->addChild(line,1);
        lines.push_back(line);
        line->runAction(getFadeAction());
    }
    for (int x = 0; x < cols+1; x++){
        auto line = Sprite::createWithTexture(img->getTexture());
        line->setAnchorPoint(Vec2(0, 0));
        line->setContentSize(Size(line_width, screen.height-margin*2));
        line->setPosition(Vec2(margin+x*cols_step, margin));
        line->setOpacity(0);
        this->addChild(line,1);
        lines.push_back(line);
        line->runAction(getFadeAction());
    }
    for(auto cell:cells){
        for(auto cel:cell){
            this->removeChild(cel);
        }
        cell.clear();
    }
    cells.clear();
    for (int j = 0; j < rows; j++){
        std::vector <Cell*> stack;
        for (int i = 0; i < cols; i++){
            auto cell = Cell::createCell(Vec2(margin+cols_step/2+j*cols_step, margin+rows_step/2+i*rows_step),
                                         Size(cols_step, rows_step),
                                         pause, img->getTexture());
            stack.push_back(cell);
            this->addChild(cell);
        }
        cells.push_back(stack);
    }
}

Grid::gridSize Grid::getSize(){
    return this->size;
}
bool Grid::getState(){
    return pause;
}

void Grid::nextFrame(float t){
    for (int j = 0; j < cells.size(); j++){
        for (int i = 0; i < cells[j].size(); i++){
            cells[j][i]->resetNeighbours();
        }
    }
    for (int j = 0; j < cells.size(); j++){
        for (int i = 0; i < cells[j].size(); i++){
            if(cells[j][i]->isAlive()){
                if((j+1)<cells.size()){
                    cells[j+1][i]->addNeighbour();
                }
                if((i+1)<cells[j].size()){
                    cells[j][i+1]->addNeighbour();
                }
                if((j-1)>0){
                    cells[j-1][i]->addNeighbour();
                }
                if((i-1)>0){
                    cells[j][i-1]->addNeighbour();
                }
                if((j+1)<cells.size()&&(i+1)<cells[j].size()){
                    cells[j+1][i+1]->addNeighbour();
                }
                if((j+1)<cells.size()&&(i-1)<cells[j].size()){
                    cells[j+1][i-1]->addNeighbour();
                }
                if((j-1)<cells.size()&&(i-1)<cells[j].size()){
                    cells[j-1][i-1]->addNeighbour();
                }
                if((j-1)<cells.size()&&(i+1)<cells[j].size()){
                    cells[j-1][i+1]->addNeighbour();
                }
            }
        }
    }
    for (int j = 0; j < cells.size(); j++){
        for (int i = 0; i < cells[j].size(); i++){
            if((cells[j][i]->getNeighbours()<2) || (cells[j][i]->getNeighbours()>3)){
                cells[j][i]->setAlive(false);
            }
            if(cells[j][i]->getNeighbours()==3){
                cells[j][i]->setAlive(true);
            }
        }
    }
}

void Grid::setVel(int vel){
    this->unschedule(schedule_selector(Grid::nextFrame));
    this->speed = (100-vel)/50 + 0.1;
    this->schedule(schedule_selector(Grid::nextFrame), speed);
}
