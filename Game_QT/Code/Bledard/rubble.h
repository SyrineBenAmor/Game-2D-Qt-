#ifndef RUBBLE_H
#define RUBBLE_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Rubble: public QObject,public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Rubble();
signals:
    void impact();
public slots:
    void move();
private:
    float rubbleSize ;
    int rotationAngle;
    float stepTillOffScreen;
};

#endif // RUBBLE_H
