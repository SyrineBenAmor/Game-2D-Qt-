#ifndef LIFEBUOY_H
#define LIFEBUOY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Lifebuoy: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Lifebuoy();
    QTimer* lifebuoyTimer;

private slots:
    void move();

private:
    float lifebuoySize;
    float stepTillOffScreen;
    bool arrived    ;
    int clickedX    ;
    int clickedY    ;
    int lifebuoyX   ;
    int lifebuoyY   ;
    int distX       ;
    float stepX     ;
    float stepY     ;
    float distXTraveled;
};

#endif // LIFEBUOY_H
