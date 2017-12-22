#include "police.h"
#include <QDebug>
#include "game.h"
#include <time.h>
#include <stdlib.h>
#include <typeinfo>

extern Game * game;
Police::Police(){
    collidedWithPlayer = false;
    policeSize     = policeSizeInit  ;
    // set random position
    //srand(1245);
    random_position = ( rand() % (int(game->scene->width())-policeSizeMax) ) + policeSizeMax/2 - policeSizeInit/2;
    setPos(random_position,spawnPostion*int(game->scene->height()));
    int playerMiddleX = game->player->x() + playerWidth/2;
    int policeMiddleX = this->x() + policeSize/2;
    int distX = playerMiddleX - policeMiddleX;
    int playerMiddleY = game->player->y() + playerHeight/2;
    int policeMiddleY = this->y() + policeSize/2;
    int distY = playerMiddleY - policeMiddleY;
    stepX = float(distX) / std::max(abs(distX),distY);
    stepY = float(distY) / std::max(abs(distX),distY);
    //load image
    if (random_position/2 < game->player->x() + playerWidth/2){
        policeImage.load(":/Images/resources/Images/police.png");
    }
    else {
        policeImage.load(":/Images/resources/Images/policeInverted.png");
    }
    setPixmap(policeImage.scaled(policeSize, policeSize,Qt::IgnoreAspectRatio));
    stepTillOffScreen =float(policeSizeMax - policeSizeInit) / (game->scene->height()-spawnPostion*game->scene->height());
    //move Police when the timer count is NULL
    QTimer * timer = new QTimer() ;
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    //timer->start(10 + (rand()%30));    // Some enemies are slow others are faster
    timer->start(5);
}

void Police::move(){
    if (!collidedWithPlayer){
        collidedWithPlayer = true;
        QList<QGraphicsItem *> colling_items = collidingItems(); // get colling items with this object
        for (size_t i=0,n=colling_items.size() ; i<n ; i++){
            if(typeid(*(colling_items[i]))==typeid(Player)){ //if this object collides with player
                game->health->decrease(50);                   // decrease health
            }
        }
    }


    //***********  Move police Down ******************

    if (pos().y() > int(game->scene->height())){
        //  Decrase Health
        game->health->decrease();
        //  Remove Object From Scene
        scene()->removeItem(this);
        //  Delete Object ( Free Memory occupied )
        delete this;
    }
    else {
        setPos(this->x()+stepX, this->y() + stepY);
    }
    // load image
    if (random_position/2 < game->player->x() + playerWidth/2){
        policeImage.load(":/Images/resources/Images/police.png");
    }
    else {
        policeImage.load(":/Images/resources/Images/policeInverted.png");
    }
    //*************  Scale police  ********************
    if (policeSize < policeSizeMax){
        policeSize    += stepTillOffScreen ;
        setPixmap(policeImage.scaled(policeSize,policeSize,Qt::IgnoreAspectRatio));
        setPos(x()- 0.5*stepTillOffScreen ,y()-0.5);
    }
}


