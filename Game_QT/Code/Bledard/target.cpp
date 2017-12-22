#include "target.h"
#include "declarations.h"
#include "game.h"
extern Game* game;
Target::Target(){
    QPixmap target(":/Images/resources/Images/target.png");
    setPixmap(target.scaled(targetSize,targetSize,Qt::IgnoreAspectRatio));
    setPos(game->getClickX() - 0.5*targetSize , game->getClickY() - 0.5*targetSize);
}

