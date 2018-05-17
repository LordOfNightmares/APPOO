#include "Health.h"
#include <QFont>

Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // initialize the score to 0
    health = 3;

    // draw the text
    setPlainText(QString("Health: ") + QString::number(health)); // Health: 3
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
}

void Health::decrease(){
    health--;
    if (health<=0){ setPlainText(QString("GameOver"));}
    else {setPlainText(QString("Health: ") + QString::number(health));} // Health: 2
}

int Health::getHealth(){
    return health;
}
void Health::setHealth(int hp){
    health = hp;
}

