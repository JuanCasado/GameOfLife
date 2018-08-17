//
//  Menu.cpp
//  GameOfLife
//
//  Created by Juan Casado Ballesteros on 7/21/18.
//

#include "SideMenu.hpp"

USING_NS_CC;

SideMenu::SideMenu(Grid * grid){
    this->grid = grid;
}

SideMenu * SideMenu::createSideMenu(Grid * grid){
    SideMenu * sideMenu = new SideMenu(grid);
    if (sideMenu && sideMenu->init()){
        sideMenu->autorelease();
        return sideMenu;
    }else{
        delete sideMenu;
        sideMenu = nullptr;
        return nullptr;
    }
}

bool SideMenu::init(void){
    if (!Scene::init()){
        return false;
    }
    background = getBackground();
    if (background==nullptr){
        return false;
    }
    auto img = Sprite::create("WhiteRect.png");
    if (img==nullptr){
        delete img;
        return false;
    }
    auto label = Label::createWithTTF("Game of Life", "fonts/Marker Felt.ttf", 26);
    if (label==nullptr){
        delete label;
        return false;
    }
    Vector<MenuItem*> menuItems;
    label->setColor(Color3B(20, 50, 0));
    auto buttonSize = Size(label->getContentSize().width*1.1, label->getContentSize().height*1.1);
    
    auto pauseSelected = Sprite::createWithTexture(img->getTexture());
    pauseSelected->setColor(Color3B(label->getColor()));
    pauseSelected->setContentSize(buttonSize);
    auto pauseBtt = Sprite::createWithTexture(img->getTexture());
    pauseBtt->setColor(Color3B(120, 200, 100));
    pauseBtt->setContentSize(buttonSize);
    pauseLabel = Label::createWithTTF("Pause", "fonts/Marker Felt.ttf", 20);
    pauseLabel->setPosition(buttonSize.width/2, buttonSize.height/2);
    auto pause = MenuItemSprite::create(pauseBtt, pauseSelected, CC_CALLBACK_0(SideMenu::pauseClicked, this));
    pause->addChild(pauseLabel);
    
    largeBtt = Sprite::createWithTexture(img->getTexture());
    largeBtt->setColor(Color3B(120, 200, 100));
    largeBtt->setContentSize(buttonSize);
    auto largeSelected = Sprite::createWithTexture(img->getTexture());
    largeSelected->setColor(Color3B(label->getColor()));
    largeSelected->setContentSize(buttonSize);
    auto largeLabel = Label::createWithTTF("Large", "fonts/Marker Felt.ttf", 20);
    largeLabel->setPosition(buttonSize.width/2, buttonSize.height/2);
    auto large = MenuItemSprite::create(largeBtt, largeSelected, CC_CALLBACK_0(SideMenu::largeClicked, this));
    large->addChild(largeLabel);
    
    mediumBtt = Sprite::createWithTexture(img->getTexture());
    mediumBtt->setColor(Color3B(140, 220, 90));
    mediumBtt->setContentSize(buttonSize);
    auto mediumSelected = Sprite::createWithTexture(img->getTexture());
    mediumSelected->setColor(Color3B(label->getColor()));
    mediumSelected->setContentSize(buttonSize);
    auto mediumLabel = Label::createWithTTF("Medium", "fonts/Marker Felt.ttf", 20);
    mediumLabel->setPosition(buttonSize.width/2, buttonSize.height/2);
    auto medium = MenuItemSprite::create(mediumBtt, mediumSelected, CC_CALLBACK_0(SideMenu::mediumClicked, this));
    medium->addChild(mediumLabel);
    
    smallBtt = Sprite::createWithTexture(img->getTexture());
    smallBtt->setColor(Color3B(120, 200, 100));
    smallBtt->setContentSize(buttonSize);
    auto smallSelected = Sprite::createWithTexture(img->getTexture());
    smallSelected->setColor(Color3B(label->getColor()));
    smallSelected->setContentSize(buttonSize);
    auto smallLabel = Label::createWithTTF("Small", "fonts/Marker Felt.ttf", 20);
    smallLabel->setPosition(buttonSize.width/2, buttonSize.height/2);
    auto small_ = MenuItemSprite::create(smallBtt, smallSelected, CC_CALLBACK_0(SideMenu::smallClicked, this));
    small_->addChild(smallLabel);
    
    auto slider = ui::Slider::create();
    slider->loadBarTexture("Slider_Back.png");
    slider->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
    slider->loadProgressBarTexture("Slider_PressBar.png");
    slider->setAnchorPoint(Vec2(0, 0.5));
    slider->setPosition(Vec2(background->getContentSize().width*1.49,background->getContentSize().height*5));
    slider->setContentSize(buttonSize);
    slider->setMaxPercent(100);
    slider->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        if (type ==ui::Widget::TouchEventType::ENDED){
            ui::Slider* sl = dynamic_cast<ui::Slider*>(sender);
            this->grid->setVel(sl->getPercent());
        }
    });
    auto move = MoveTo::create(1.6, Vec2(background->getContentSize().width*1.49,background->getContentSize().height*0.29));
    slider->runAction(move);
    this->addChild(slider,2);
    
    menuItems.pushBack(MenuItemLabel::create(label));
    menuItems.pushBack(pause);
    menuItems.pushBack(large);
    menuItems.pushBack(medium);
    menuItems.pushBack(small_);
    
    auto buttonHolder = Menu::createWithArray(menuItems);
    buttonHolder->setAnchorPoint(Vec2(0, 0.5));
    buttonHolder->alignItemsVertically();
    buttonHolder->setPosition(Vec2(background->getContentSize().width*2/5,background->getContentSize().height/2));
    
    background->addChild(buttonHolder,1);
    this->addChild(background);
    background->runAction(getSlideAction());
    
    return true;
}

Spawn * SideMenu::getSlideAction(void){
    auto screen = Director::getInstance()->getSafeAreaRect().size;
    Vector<FiniteTimeAction*> actions;
    actions.pushBack(FadeTo::create(0.5, 255));
    auto move = MoveTo::create(1.5, Vec2(screen.width - (screen.width - screen.height - screen.width/40), screen.height/2));
    actions.pushBack(EaseBackOut::create(move->clone()));
    return Spawn::create(actions);
}

Sprite * SideMenu::getBackground(void){
    Sprite * background = Sprite::create("SideMenu.png");
    if (background==nullptr){
        delete background;
        return nullptr;
    }
    auto screen = Director::getInstance()->getSafeAreaRect().size;
    background->setAnchorPoint(Vec2(0, 0.5));
    background->setContentSize(Size(screen.width/2, screen.height*3/4));
    background->setPosition(Vec2(screen.width*3/2, screen.height/2));
    background->setColor(Color3B(120, 240, 100));
    return background;
}

void SideMenu::pauseClicked(void){
    this->grid->changeState();
    if(this->grid->getState()){
        this->pauseLabel->setString("Resume");
        explanation = Label::createWithTTF("click the tiles to change their state", "fonts/Marker Felt.ttf", 15);
        explanation->setColor(Color3B(20, 50, 0));
        explanation->setAnchorPoint(Vec2(0, 0));
        explanation->setPosition(Vec2(10, 4));
        background->addChild(explanation);
    }else{
        this->pauseLabel->setString("Pause");
        background->removeChild(explanation, false);
    }
}

void SideMenu::largeClicked(void){
    this->grid->setGridSize(Grid::Large);
    largeBtt->setColor(Color3B(140, 220, 90));
    mediumBtt->setColor(Color3B(120, 200, 100));
    smallBtt->setColor(Color3B(120, 200, 100));
}

void SideMenu::mediumClicked(void){
    this->grid->setGridSize(Grid::Medium);
    largeBtt->setColor(Color3B(120, 200, 100));
    mediumBtt->setColor(Color3B(140, 220, 90));
    smallBtt->setColor(Color3B(120, 200, 100));
}

void SideMenu::smallClicked(void){
    this->grid->setGridSize(Grid::Small);
    largeBtt->setColor(Color3B(120, 200, 100));
    mediumBtt->setColor(Color3B(120, 200, 100));
    smallBtt->setColor(Color3B(140, 220, 90));
}
