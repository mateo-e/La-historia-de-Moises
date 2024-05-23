#include "pared.h"

pared::pared()
{

}

pared::pared(int x, int y, int w, int h)
{
    this->posx=x;
    this->posy=y;
    this->h=h;
    this->w=w;
}

pared::pared(int x, int y, int w, int h, QString im)
{
    this->posx=x;
    this->posy=y;
    this->h=h;
    this->w=w;
    this->imageName = im;
}

QRectF pared::boundingRect() const
{
    return QRectF(posx,posy,w,h);
}

void pared::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{


    if(imageName.size() > 1) // si se quiere que la pared tenga algun aspecto en especifio
    {
        QPixmap *aspecto = new QPixmap(imageName);
        painter->drawPixmap(posx,posy,150,110,*aspecto);
    }

    else
    {
        painter->setBrush(Qt::black);
        painter->setPen(Qt::blue);
        painter->drawRect(boundingRect());
    }

}
