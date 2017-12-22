#include "player.h"
#include "game.h"
#include "declarations.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
extern Game* game;
Player::Player(){
    QPixmap playerImage(":/Images/resources/Images/player.png");
    setPixmap(playerImage.scaled(playerWidth,playerHeight,Qt::IgnoreAspectRatio));
    setPos(game->scene->width()/2 - playerWidth/2 , game->scene->height()- (playerHeight + 1));
    recoilTimer = new QTimer();
    connect(recoilTimer,SIGNAL(timeout()),this,SLOT(playerRecoil()));
    recoilTimer->start(40);
}

void Player::keyPressEvent(QKeyEvent* key_event){
    if (key_event->key() == Qt::Key_Q){
        if (pos().x()>0){
        setPos(x()-10,y());
        }
    }
    else if (key_event->key() == Qt::Key_D){
        if (pos().x() <game->scene->width()- playerWidth){
            setPos(x()+10,y());
        }
    }
}

void Player::playerRecoil(){
    if(pos().y()> game->scene->height()- playerHeight){
        setPos(this->x(),this->y()-2);
    }
}

