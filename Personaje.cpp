#include "Personaje.h"
#include <QGraphicsScene>
#include <QLabel>
#include <QPixmap>
#include <QKeyEvent>
#include <QDebug>

//Definir el jugador y la imgen
Personaje::Personaje(QGraphicsView *view,QGraphicsItem *im):QGraphicsPixmapItem(im)
{
    viewRect = view->size();
    QRectF sceneRect = view->sceneRect();
    qDebug() << viewRect << " "<< sceneRect << " "<<view->size().width();
    spriteSheet.load(":/sprites.png");

    QPixmap sprite = spriteSheet.copy(spriteX, spriteY, spriteWidth, spriteHeight);
    setPixmap(sprite);
}



void Personaje::keyPressEvent(QKeyEvent *event)
{
    //Manejo del evento de tecla
    switch(event->key()) {
    case Qt::Key_A:

        moveBy(-5, 0);
        //setSprite(60);
        break;
    case Qt::Key_D:

        moveBy(5, 0);
        //setSprite(120);
        break;
    case Qt::Key_W:

        moveBy(0, -5);
        break;
    case Qt::Key_S:

        moveBy(0, 5);
        break;
    default:
        QGraphicsItem::keyPressEvent(event);
    }
}

QRectF Personaje::boundingRect() const
{

}

void Personaje::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void Personaje::moveBy(int dx, int dy)
{
    x += dx;
    y += dy;
    if (x>viewRect.width()-50||x<0){
        x-=dx;
    }
    setPos(x, y);
}

void Personaje::setSprite(int dir)
{
    spriteX = 60*cont;
    spriteY = dir;
    QPixmap sprite = spriteSheet.copy(spriteX, spriteY, spriteWidth, spriteHeight);
    setPixmap(sprite);
    cont++;
    if(cont==7){cont=0;}
}
