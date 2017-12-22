#include "drowning_man.h"
#include "game.h"
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h>
#include <QLabel>

extern Game * game ;
Drowning_man::Drowning_man(){

    drowningManSize = drowningManSizeInit ;

    // set random position
    int random_pos = ( rand() % (int(game->scene->width())-drowningManSizeMax) ) + drowningManSizeMax/2 - drowningManSize/2;
    setPos(random_pos,spawnPostion*game->scene->height());

    // insert enemy
    QPixmap drowningManImage(":/Images/resources/Images/Dman.png");
    setPixmap(drowningManImage.scaled(drowningManSize, drowningManSize,Qt::IgnoreAspectRatio));
    stepTillOffScreen =float(drowningManSizeMax - drowningManSizeInit) / (game->scene->height()-spawnPostion*game->scene->height());
    // connect
    QTimer * timer = new QTimer ;
    connect(timer, SIGNAL(timeout()),this,SLOT(move()));
    timer->start(200);
}

void Drowning_man::move(){

    //***********  Move Drowning man Down ******************
    if (pos().y() > int(game->scene->height())){
        //remove Drowning man
        game->scene->removeItem(this);
        //delete
        delete this;
    }
    else setPos(x(),y()+1);

// ************************Scale Drowning Man**********************

    if (drowningManSize < drowningManSizeMax){
        drowningManSize    += stepTillOffScreen ;
        QPixmap drowningManImage(":/Images/resources/Images/Dman.png");
        setPixmap(drowningManImage.scaled(drowningManSize,drowningManSize,Qt::IgnoreAspectRatio));
        setPos(x()- 0.5*stepTillOffScreen ,y());
    }
}




