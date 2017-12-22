#ifndef POLICE_H
#define POLICE_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Police: public QObject,public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Police();
public slots:
    void move();
private :
    int random_position;
    float policeSize  ;
    float stepTillOffScreen;
    bool collidedWithPlayer;
    float stepX;
    float stepY;
    QPixmap policeImage;

};

#endif // POLICE_H
