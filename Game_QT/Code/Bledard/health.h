#ifndef HEALTH
#define HEALTH


#include <QGraphicsTextItem>

class Health: public QGraphicsTextItem{
    Q_OBJECT
public:
    Health(QGraphicsItem * parent = 0);
    void decrease(int damage = 20);
    int getHealth();
signals:
    void dead();
private:
    int health;
};


#endif // HEALTH

