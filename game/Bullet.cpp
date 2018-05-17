#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "Enemy.h"
#include "Game.h"

extern Game * game; // there is an external global object called game

Bullet::Bullet(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){

    // draw graphics
    setPixmap(QPixmap(":/images/bullet.png").scaledToWidth(25, Qt::SmoothTransformation));
    // make/connect a timer to move() the bullet every so often
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    // start the timer
    timer->start(50);
}

void Bullet::move(){
    // get a list of all the items currently colliding with this bullet
    QList<QGraphicsItem *> bullets = collidingItems();

    // if one of the colliding items is an Enemy, destroy both the bullet and the enemy
    for (int i = 0, n = bullets.size(); i < n; ++i){
        if (typeid(*(bullets[i])) == typeid(Enemy)){
            // increase the score
            game->score->increase();

            // remove them from the scene (still on the heap)
            scene()->removeItem(bullets[i]);
            scene()->removeItem(this);

            // delete them from the heap to save memory
            delete bullets[i];
            delete this;

            // return (all code below refers to a non existint bullet)
            return;
        }
    }

    // if there was no collision with an Enemy, move the bullet forward
    setPos(x(),y()-10);
    // if the bullet is off the screen, destroy it
    if (pos().y() < 0){
        scene()->removeItem(this);
        delete this;
    }
}
