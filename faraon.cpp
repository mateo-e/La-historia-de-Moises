#include "faraon.h"

faraon::faraon(qreal _x, qreal _y) : Personaje(_x,_y)
{
    spriteX = 396;
    dir = 'a';

    image = new QPixmap(":/sprites/sprite.png");

    setPos(_x,_y);
}

QRectF faraon::boundingRect() const
{
    return QRectF(x,y,66, 66);
}

void faraon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(dir == 's')
    {
        painter->drawPixmap(x,y,*image,spriteX,0,67,67);
    }
    else if (dir == 'a')
    {
        painter->drawPixmap(x,y,*image,spriteX,67,67,67);
    }
    else if (dir == 'd')
    {
        painter->drawPixmap(x,y,*image,spriteX,134,67,67);
    }
    else if (dir == 'w')
    {
        painter->drawPixmap(x,y,*image,spriteX,202,67,67);
    }
}
