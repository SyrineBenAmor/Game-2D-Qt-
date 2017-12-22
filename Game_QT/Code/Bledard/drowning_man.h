#ifndef DROWNING_MAN_H
#define DROWNING_MAN_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Drowning_man: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Drowning_man();
public slots:
    void move();
private:
    float drowningManSize ;
    float stepTillOffScreen;

};

#endif // DROWNING_MAN_H
