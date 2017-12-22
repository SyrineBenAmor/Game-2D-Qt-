#ifndef GAME
#define GAME

#include "declarations.h"
#include "player.h"
#include "score.h"
#include "health.h"
#include "button.h"
#include "rubble.h"
#include "police.h"
#include "target.h"
#include <stdlib.h>
#include "soundicon.h"

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QTimer>
#include <QMouseEvent>

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game();
    QGraphicsScene * scene;
    Player * player;
    Score * score;
    Health * health;
    SoundIcon * soundIcon ;
    Target* target;
    QMediaPlayer * musicPlayer ;
    QTimer * policeTimer;
    QTimer* rubbleTimer ;
    QTimer* drowningManTimer;
    int getClickX();
    int getClickY();

protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
signals:
    void moved();
public slots:
    void displayMainMenu();
    void displayGameOverWindow();
    void spawn_rubble();
    void spawn_police();
    void spawn_drowningman();
    void startGame();
    void moveTarget();
private:
   void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
   void addLifebuoy();
   bool mainMenuOnScreen;
   bool gameStarted ;
   bool gameOver;
   int clickX;
   int clickY;
};

#endif // GAME





