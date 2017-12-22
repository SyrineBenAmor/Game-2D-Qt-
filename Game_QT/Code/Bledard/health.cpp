#include "health.h"
#include <QFont>

Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent){
    //initialize the health to 4
    health = 100;
    //draw the text
   setPlainText(QString("Health: ") + QString:: number(health)); //Health: 4
   setDefaultTextColor(Qt::white);
   setFont(QFont("times",16));
}

void Health::decrease(int damage){
    if (health >0) health -= damage;
    setPlainText(QString("Health: ") + QString:: number(health)); //Health: x
    if( health <= 0 ) emit dead();
}

int Health::getHealth(){
    return health;
}
