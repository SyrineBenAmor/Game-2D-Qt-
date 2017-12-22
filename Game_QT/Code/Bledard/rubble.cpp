#include "rubble.h"
#include "game.h"
#include <QGraphicsPixmapItem>
#include <stdlib.h>
#include <typeinfo>
extern Game * game;
Rubble::Rubble(){
    rubbleSize    = rubbleSizeInit  ;

    QPixmap rubbleImage(":/Images/resources/Images/rubble.png");
    setPixmap(rubbleImage.scaled(rubbleSize,rubbleSize,Qt::IgnoreAspectRatio));
    rotationAngle = 0;
    int random_position = rand() %(int(game->scene->width()-rubbleSizeMax));
    setPos(random_position, spawnPostion * game->scene->height());// spawn at a certain location what ever the size of the scene is
    stepTillOffScreen =float(rubbleSizeMax - rubbleSizeInit) / (game->scene->height()- spawnPostion*game->scene->height());
    QTimer * moveTimer = new QTimer();
    connect(moveTimer,SIGNAL(timeout()),this,SLOT(move()));
    //timer->start(50+rand()%100);
    moveTimer->start(50);
}

void Rubble::move(){
    QList<QGraphicsItem *> colling_items = collidingItems(); // get colling items with this object
    for (size_t i=0,n=colling_items.size() ; i<n ; i++){
        if(typeid(*(colling_items[i]))==typeid(Player)){ //if this object collides with player
            emit impact();
            game->health->decrease();                   // decrease health
            //Player will get a shoc and recoil
            game->player->setPos(game->player->x(),game->scene->height()- 2*playerHeight/3);

            int rubbleCenter = pos().x() + rubbleSize/2;
            int playerCenter = game->player->x()+playerWidth/2;
            if ((rubbleCenter > playerCenter) & (rotationAngle!=30)){
                // rubble is colling with the top right side of the player
                rotationAngle = 30 ;
                int offset = playerWidth/2 + rubbleSize/2 - (rubbleCenter - playerCenter);
                setPos(pos().x() + 10 +offset, pos().y()-20);
            }
            else if((rubbleCenter > playerCenter) & (rotationAngle==30)) {
                setPos(pos().x() + 20, pos().y());
            }
            if((rubbleCenter < playerCenter) & (rotationAngle!=-20)) {
                // rubble is colling with the top left side of the player
                int offset = playerWidth/2 + rubbleSize/2 - (playerCenter - rubbleCenter);
                rotationAngle = -20;
                setPos(pos().x() - 10 - offset, pos().y()+40);
            }
            else if((rubbleCenter < playerCenter) & (rotationAngle==-20)){
                setPos(pos().x() - 30, pos().y());
            }
            setRotation(rotationAngle);
        }
    }
    if(rotationAngle>0) {
        setPos(pos().x()+1, pos().y()+1);   //rubble on the right side
    }
    else if (rotationAngle<0) {
        setPos(pos().x()-1, pos().y()+1);                  //rubble on the left side
    }
    if (pos().y() > game->scene->height()){
        //  Remove Object From Scene
        scene()->removeItem(this);
        //  Delete Object ( Free Memory occupied )
        delete this;
    }
    else {
        setPos(x(),y()+1);
    }

    //*************  Scale rubble  ********************
    if (rubbleSize < rubbleSizeMax){
        rubbleSize    += stepTillOffScreen ;
        QPixmap rubbleImage(":/Images/resources/Images/rubble.png");
        setPixmap(rubbleImage.scaled(rubbleSize,rubbleSize,Qt::IgnoreAspectRatio));
        setPos(x()- 0.5*stepTillOffScreen ,y());
    }
}

