#include "faraon.h"

faraon::faraon(qreal _x, qreal _y) : Personaje(_x,_y)
{
    spriteX = 396;
    dir = 'a';
    vidas = 1;

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

void faraon::setSprite()
{
    spriteX = 67*cont + 396;
    cont++;
    if(cont==3){cont=0;}
}

void faraon::despl_x()
{
    if(x < 600 and 597 <= x)
        dir = 'a';
    else if(x < 400 and 397 <= x)
        dir = 'd';
    if(dir == 'd')
        moveBy(2,0);
    else if(dir == 'a')
        moveBy(-2,0);

    setSprite();

}
