#ifndef PLAYER
#define PLAYER

#include <QGraphicsPixmapItem>
#include <QObject>

class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player();
    void keyPressEvent(QKeyEvent *key_event);
private slots:
    void playerRecoil();
private:
    QTimer* recoilTimer;
};


#endif // PLAYER

