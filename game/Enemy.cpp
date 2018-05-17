#include "Enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int
#include "Game.h"

extern Game * game;

Enemy::Enemy(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    if (game->health->getHealth()<=0)
    {
        setPos(350,0);
        setPixmap(QPixmap(":/images/gameOver.png").scaledToWidth(200, Qt::SmoothTransformation));
    }
    else
    {
    //set random x position
    int random_number = rand() % 700;
    setPos(random_number,0);

    // drew the rect
    setPixmap(QPixmap(":/images/enemy.png").scaledToWidth(100, Qt::SmoothTransformation));
    }
    setTransformOriginPoint(100,100);

    // make/connect a timer to move() the enemy every so often
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    // start the timer
    timer->start(60);
}

void Enemy::move(){
    // move enemy down

    setPos(x(),y()+5);

    // destroy enemy when it goes out of the screen
    if (pos().y() > 600){
        //decrease the health
        game->health->decrease();

        scene()->removeItem(this);
        delete this;
    }
}
