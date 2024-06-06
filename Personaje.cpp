#include "Personaje.h"

void Personaje::saltar()
{
    y = posY_in - (40 * tiempoTrans) + (0.5*9.8 * tiempoTrans * tiempoTrans);
    setPos(x,y);
}

Personaje::Personaje(qreal _x, qreal _y)
{
    x = _x;
    y = _y;
    spriteX = 201;
    vidas = 3;
    posY_in = _y;

    image = new QPixmap (":/sprites/sprite.png");

    setPos(_x,_y);
}

Personaje::Personaje(qreal _x, qreal _y, char _aspecto)
{
    x = _x;
    y = _y;

    aspecto = _aspecto;

    switch(aspecto)
    {
    case '1': spriteX = 67*cont + 201; break;
    case '2': spriteX = 67*cont + 402; break;
    case '3': spriteX = 67*cont + 603; break;
    }

    image = new QPixmap (":/sprites/sprite.png");

    setPos(_x,_y);
}



QRectF Personaje::boundingRect() const
{
    return QRectF(x+5,y+5,45, 58);
}

void Personaje::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void Personaje::moveBy(short dx,short dy)
{
    x += dx;
    y += dy;
    setPos(x, y);
}

void Personaje::setSprite()
{
    switch(aspecto)
    {
    case '1': spriteX = 67*cont + 201; break;
    case '2': spriteX = 67*cont + 402; break;
    case '3': spriteX = 67*cont + 603; break;
    }
    cont++;
    if(cont==3){cont=0;}
}


