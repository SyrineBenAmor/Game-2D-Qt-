#include "game.h"
#include "lifebuoy.h"
#include "drowning_man.h"
#include <QLabel>
#include <QMovie>
#include <time.h>
#include <QIcon>
#include <QGraphicsTextItem>
#include <QBrush>
#include <QFont>
#include <QImage>
#include <QDebug>

Game:: Game(){
    //this->setWindowIcon(QIcon(":/Images/resources/Images/mainMenuBackground.ico"));
    // create a scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,sceneWidth,sceneHeight);
    //scene->setSceneRect(0,0,this->width(),this->height());
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // deactivate scrollbars
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(sceneWidth,sceneHeight);
    soundIcon = new SoundIcon();
    soundIcon->setPos(scene->width()-soundIconSize,0);
}
void Game::spawn_rubble(){
    //create rubble
    Rubble * rubble = new Rubble();
    scene->addItem(rubble);
}

void Game::spawn_police(){
    // create enemy
    Police * police = new Police();
    scene->addItem(police);
}

void Game::spawn_drowningman(){
    Drowning_man * man = new Drowning_man();
    scene->addItem(man);
}

void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity){
    // draw panel at the specified location with the specified properties
    QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}

void Game::startGame(){
    mainMenuOnScreen = false;
    gameStarted = false;
    gameOver    = false;
    //******************************************************************
    // create a scene
    scene = new QGraphicsScene();
    scene->clear();
    scene->setSceneRect(0,0,sceneWidth,sceneHeight);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // deactivate scrollbars
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setFixedSize(scene_width,scene_height);

    QLabel *bg = new QLabel;
    QMovie *mv = new QMovie(":/Images/resources/Images/bg.gif");
    bg->setMovie(mv);
    mv->start();
    bg->setScaledContents(true);
    bg->setGeometry(0,0,scene->width(),scene->height());
    scene->addWidget(bg);
    //********************************************************************


    //************************Sound Icon**********************************
    scene->addItem(soundIcon);
    //********************************************************************


    //*****************************Player*********************************
    player = new Player();
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);
    //********************************************************************


    //*****************************Policia********************************
    // spawn police
    policeTimer =new QTimer();
    connect(policeTimer,SIGNAL(timeout()),this,SLOT(spawn_police()));
    policeTimer->start(2000);
    //********************************************************************


    //*****************************Rubble*********************************
    // spawn rubble
    rubbleTimer =new QTimer();
    connect(rubbleTimer,SIGNAL(timeout()),this,SLOT(spawn_rubble()));
    rubbleTimer->start(5000);
    //********************************************************************


    //*****************************Drowning Man***************************
    // spawn Drowning Man
    drowningManTimer =new QTimer();
    connect(drowningManTimer,SIGNAL(timeout()),this,SLOT(spawn_drowningman()));
    drowningManTimer->start(6000);
    //********************************************************************


    //****************************Score Health****************************
    //create score
    score = new Score();
    scene->addItem(score);

    //create health
    health = new Health();
    health->setPos(health->x(),health->y()+25);
    scene->addItem(health);
    // If health = 0 display game over
    connect(health,SIGNAL(dead()),this,SLOT(displayGameOverWindow()));
    //********************************************************************


    //*****************************Target*********************************
    target= new Target();
    scene->addItem(target);
    connect(this,SIGNAL(moved()),this,SLOT(moveTarget()));
    //********************************************************************


    //***************************Music Player*****************************
    musicPlayer->stop();
    musicPlayer->setMedia(QUrl("qrc:/music/resources/Music/Taylor Davis.mp3"));
    musicPlayer->play();
    //********************************************************************

    //show the view
    show();
}

void Game::moveTarget(){
    target->setPos(clickX-targetSize/2,clickY-targetSize/2);
}

void Game::displayMainMenu() {
    //scene = new QGraphicsScene();
    //scene->clear();
    mainMenuOnScreen = true;
    //********************* SET THE BACKGROUND *************************
    // use this for static image as Background

    QPixmap BackgroundImage(":/Images/resources/Images/mainMenuBackground.png");// set the background image
    BackgroundImage.scaled(scene->width(),scene->height(),Qt::IgnoreAspectRatio);
    setBackgroundBrush(QBrush(BackgroundImage));


    /*
     * //*************************Text Title*******************************
    //create title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Bled-art"));
    QFont titleFont("comic sans",50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);
    //*****************************************************************
    */

    /*
     * //************************Game Title*******************************
    QPixmap logo(":/Images/resources/Images/Logo.png");
    QLabel * Logo = new QLabel();
    Logo->setPixmap(logo);
    int logo_x = this->width()/2 - logo.width()/2;
    int logo_y = 150 ;
    Logo->setGeometry(logo_x,logo_y,logo.width(),logo.height());
    scene->addWidget(Logo);
    //********************************************************************
    */

    //************************Sound Icon**********************************
    scene->addItem(soundIcon);
    //********************************************************************


    //************************Play Button*********************************
    //create play button
    Button * playButton = new Button(QString("Play"));
    int play_button_x = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos= 300;
    playButton->setPos(play_button_x,byPos);
    connect(playButton,SIGNAL(clicked()), this,SLOT(startGame()));
    scene->addItem(playButton);
    //********************************************************************



    //*************************Quit Button********************************
    // create quit button
    Button* quit = new Button(QString("Quit"));
    int quit_button_x = play_button_x;
    quit->setPos(quit_button_x,375);
    scene->addItem(quit);
    connect(quit,SIGNAL(clicked()),this,SLOT(close()));
    //********************************************************************


    //***************************Music Player*****************************
    musicPlayer = new QMediaPlayer();
    musicPlayer->setMedia(QUrl("qrc:/music/resources/Music/Wala Lela.mp3"));
    musicPlayer->play();
    //********************************************************************
}

int Game::getClickX(){
    return clickX;
}

int Game::getClickY(){
    return clickY;
}

void Game::mouseMoveEvent(QMouseEvent *event){
    //qDebug() << QString::number(event->pos().y());
    clickX  = event->x();
    clickY  = event->y();
    emit moved();
    QGraphicsView::mouseMoveEvent(event);
}

void Game::mouseReleaseEvent(QMouseEvent *event){
    if((mainMenuOnScreen==false) & (!gameStarted)) gameStarted = true;
    else if ((mainMenuOnScreen==false) & (gameStarted) ){
        //create a lifebuoy
        addLifebuoy();
        player->setFocus(); // unable to move the player after click ==> setfocus on player again
        QGraphicsView::mouseMoveEvent(event);
    }
}

void Game::addLifebuoy(){
    if(gameStarted & !gameOver & (clickX < scene->width()-soundIconSize) & (clickY>soundIconSize)){
        //qDebug() << "lifebuoy created";
        Lifebuoy* lifebuoy = new Lifebuoy();
        scene->addItem(lifebuoy);
    }
}


void Game::displayGameOverWindow() {
    gameOver = true ;
    policeTimer->disconnect();
    rubbleTimer->disconnect();
    drowningManTimer->disconnect();
    health->disconnect();

    //Draw background Dark Transparent
    drawPanel(0,0,scene->width(),scene->height(),Qt::black,0.65);

    //Draw Gray transparent
    drawPanel(scene->width()/4,scene->height()/2-scene->width()/4,scene->width()/2,scene->width()/2,Qt::lightGray,0.75);

    //create title text
    QGraphicsTextItem * titleText = new QGraphicsTextItem(QString("DEPORTED"));
    QFont titleFont("comic sans",50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = scene->height()/2-scene->width()/4 + 50 ;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    //create playAgain button
    Button* playAgain= new Button(QString("Try Again"));
    playAgain->setPos(scene->width()/2 - buttonWidth/2,300);
    scene->addItem(playAgain);
    connect(playAgain,SIGNAL(clicked()),this,SLOT(startGame()));

    //create the quit button
    Button* quit = new Button(QString("Quit"));
    quit->setPos(scene->width()/2 - buttonWidth/2,360);
    scene->addItem(quit);
    connect(quit,SIGNAL(clicked()),this,SLOT(close()));
}
