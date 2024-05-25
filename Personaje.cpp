#include "Personaje.h"

//Definir el jugador y la imgen

bool Personaje::getBandera() const
{
    return bandera;
}

void Personaje::setBandera(bool newBandera)
{
    bandera = newBandera;
}

Personaje::Personaje(qreal _x, qreal _y)
{
    x = _x;
    y = _y;
    spriteX = 201;

    image = new QPixmap (":/sprites/sprite.png");

    setPos(_x,_y);
}



QRectF Personaje::boundingRect() const
{
    return QRectF(x,y,66, 66);
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
    spriteX = 67*cont + 201;
    cont++;
    if(cont==3){cont=0;}
}
