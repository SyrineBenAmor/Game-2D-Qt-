#include "soundicon.h"
#include "game.h"
#include <QGraphicsScene>
extern Game* game;
SoundIcon::SoundIcon(){
    QPixmap soundImage(":/Images/resources/Images/sound.png");
    setPixmap(soundImage.scaled(soundIconSize,soundIconSize,Qt::IgnoreAspectRatio));
    muteStat = false ;
}

void SoundIcon::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        QPixmap soundImage(":/Images/resources/Images/sound.png");
        QPixmap muteImage (":/Images/resources/Images/mute.png");
        if(muteStat ==false){
            muteStat = true;
            setPixmap(muteImage.scaled(soundIconSize,soundIconSize,Qt::IgnoreAspectRatio));
            game->musicPlayer->setVolume(0);
        }
        else{
            muteStat = false;
            setPixmap(soundImage.scaled(soundIconSize,soundIconSize,Qt::IgnoreAspectRatio));
            game->musicPlayer->setVolume(100);
        }
    }
}
