//
//  Cell.cpp
//  GameOfLife
//
//  Created by Juan Casado Ballesteros on 7/23/18.
//

#include "Cell.hpp"

USING_NS_CC;

Cell * Cell::createCell(Vec2 pos, Size size, bool paused, Texture2D * img){
    Cell* cell = new Cell(paused);
    if (cell && cell->initWithTexture(img)){
        cell->autorelease();
        cell->addEvents();
        cell->setPosition(pos);
        cell->setContentSize(size);
        cell->newColor();
        return cell;
    }
    CC_SAFE_DELETE(cell);
    return nullptr;
}

Cell::Cell(bool paused){
    this->paused = paused;
    this->neighbours = 0;
    if (paused){
        this->alive = false;
    }else{
        this->alive = rand_minus1_1()>0?true:false;
    }
}

void Cell::addEvents(){
    listener = EventListenerTouchOneByOne::create();
    listener->retain();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [&](Touch* touch, Event* event){
        Vec2 p = touch->getLocation();
        Rect rect = this->getBoundingBox();
        if(rect.containsPoint(p)){
            if(this->isPaused())
                this->setColor(Color3B(255, 255, 0));
            return true;
        }
        return false;
    };
    listener->onTouchEnded = [=](Touch* touch, Event* event){
        Cell::onTouched();
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}

void Cell::resetNeighbours(){
    if (!paused)
        this->neighbours = 0;
}

void Cell::addNeighbour(){
    if (!paused)
        this->neighbours++;
}

bool Cell::isAlive(){
    return alive;
}

int Cell::getNeighbours(){
    return neighbours;
}

void Cell::setAlive(bool state){
    if (!paused){
        this->alive = state;
        newColor();
    }
}

void Cell::setPaused(bool state){
    this->paused = state;
}

void Cell::onTouched(){
    if (paused){
        this->alive = !this->alive;
        newColor();
    }
}

void Cell::newColor(){
    if(alive){
        
        this->setColor(Color3B(0,0,0));
    }else{
        this->setColor(Color3B(255,255,255));
    }
}

bool Cell::isPaused(){
    return paused;
}

Cell::~Cell(){
    Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
    listener->release();
}
