#include "villano.h"

villano::villano(qreal _x, qreal _y) : Personaje(_x,_y)
{
    spriteX = 0;
    dir = 'a';
    vidas = 3;
    image = new QPixmap(":/sprites/sprite.png");

    setPos(_x,_y);
}

QRectF villano::boundingRect() const
{
    return QRectF(x,y,74,72);
}

void villano::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(dir == 's')
    {
        painter->drawPixmap(x,y,*image,spriteX + 2,3,60,67);
    }
    else if (dir == 'a')
    {
        painter->drawPixmap(x,y,*image,spriteX + 2,70,60,67);
    }
    else if (dir == 'd')
    {
        painter->drawPixmap(x,y,*image,spriteX,137,60,67);
    }
    else if (dir == 'w')
    {
        painter->drawPixmap(x,y,*image,spriteX + 2,205,55,67);
    }
}

void villano::setSprite()
{
    if(es_faraon)
    {
        spriteX = 67*cont;
        cont++;
        if(cont==3){cont=0;}
    }
    else
    {
        spriteX = 67*cont + 800;
        cont++;
        if(cont==3){cont=0;}
    }
}

void villano::despl_x()
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
