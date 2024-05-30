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


    if(imageName == ":/sprites/puntos_apuntado.png") // si se quiere que la pared tenga algun aspecto en especifio
    {
        QPixmap *aspecto = new QPixmap(imageName);
        painter->drawPixmap(posx,posy,largoTotal,30,*aspecto);
    }
    else if(imageName == ":/sprites/cactus.png")
    {
        QPixmap *aspecto = new QPixmap(imageName);
        painter->drawPixmap(posx,posy,*aspecto,cont*200,0,200,170);
    }
    else if(imageName == ":/sprites/casas.png")
    {
        QPixmap *aspecto = new QPixmap(imageName);
        painter->drawPixmap(posx,posy,*aspecto,cont*350,0,350,300);
    }
    else if(imageName == ":/sprites/marco_pintado.png")
    {
        QPixmap *aspecto = new QPixmap(imageName);
        painter->drawPixmap(posx,posy,w,h,*aspecto);
    }
    else if(imageName == ":/sprites/brocha.png")
    {
        QPixmap *aspecto = new QPixmap(imageName);
        painter->drawPixmap(posx,posy,w,h,*aspecto);
    }
    else
    {
        painter->setBrush(Qt::black);
        painter->setPen(Qt::blue);
        painter->drawRect(boundingRect());
    }

}
