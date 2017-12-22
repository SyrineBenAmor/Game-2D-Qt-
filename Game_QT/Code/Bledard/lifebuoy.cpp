#include "lifebuoy.h"
#include "declarations.h"
#include "drowning_man.h"
#include "game.h"
//#include <QThread>
#include <QDebug>
#include <typeinfo>
extern Game* game;
Lifebuoy::Lifebuoy(){
    lifebuoySize = lifebuoySizeInit;
    QPixmap lifebuoyImage(":/Images/resources/Images/lifebuoy.png");
    setPixmap(lifebuoyImage.scaled(lifebuoySize,lifebuoySize,Qt::IgnoreAspectRatio));
    distXTraveled = 0;
    arrived = false;
    lifebuoyX = game->player->x() - 50;
    lifebuoyY = game->player->y() - lifebuoySizeInit/2;
    clickedX = game->getClickX();
    clickedY = game->getClickY();
    setPos(lifebuoyX, lifebuoyY);

    lifebuoyX += lifebuoySize/2 ;//use the center of the lifebuoy as reference
    lifebuoyY += lifebuoySize/2 ;//********************************************for movement
    distX = clickedX - lifebuoyX;
    int distY = clickedY - lifebuoyY ;
    stepX     = float(distX) / std::max(abs(distX),abs(distY)) ;
    stepY     = float(distY) / std::max(abs(distX),abs(distY)) ;
    lifebuoyTimer = new QTimer();
    connect(lifebuoyTimer,SIGNAL(timeout()),this,SLOT(move()));
    lifebuoyTimer->start(10);
}

void Lifebuoy::move(){
    //get a list of all items currently colliding with this lifebuoy
    QList<QGraphicsItem *> colliding_items = collidingItems();
    // if lifebuoy collide with a drowning man
    for(int i = 0, n=colliding_items.size(); i < n; ++i){
        if(typeid(*(colliding_items[i])) == typeid(Drowning_man)){
            //increase the score
            game->score->increase();
            //remove them both
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            //delete them both
            delete colliding_items[i];
            delete this;
            qDebug() << "MAN SAVED";
            return;
        }
    }

    QPixmap lifebuoyImage(":/Images/resources/Images/lifebuoy.png");
    if (abs(distXTraveled) < abs(distX)){ // lifebuoy not arrived to desired location
        // if still moving to click location
        if (lifebuoySize>lifebuoySizeMin){ // resize image and shift reference to center
            lifebuoySize--;
            setPixmap(lifebuoyImage.scaled(lifebuoySize,lifebuoySize,Qt::IgnoreAspectRatio));
            setPos(this->x()+stepX+0.5,this->y()+stepY+0.5);
        }// else move lifebuoy
        else setPos(this->x()+stepX,this->y()+stepY);
        distXTraveled += stepX ;
        if (abs(distXTraveled) == abs(distX)) {
            arrived = true;
            stepTillOffScreen = float(lifebuoySizeInit-lifebuoySize)/(game->scene->height()-this->y());
        }
    }
    if (arrived){ // when lifebuoy has arrived to click position ==> move down and magnify
        lifebuoySize += stepTillOffScreen;
        setPixmap(lifebuoyImage.scaled(lifebuoySize,lifebuoySize,Qt::IgnoreAspectRatio));
        setPos(this->x() - 0.5*stepTillOffScreen, this->y() + 1 - 0.5*stepTillOffScreen);
    }
    if (this->y()>game->scene->height()) {
        scene()->removeItem(this);
        delete this;

    }
}
