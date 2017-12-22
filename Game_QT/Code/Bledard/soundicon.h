#ifndef SOUNDICON_H
#define SOUNDICON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class SoundIcon:public QGraphicsPixmapItem{
public:
    SoundIcon();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    bool muteStat       ;
};

#endif // SOUNDICON_H
