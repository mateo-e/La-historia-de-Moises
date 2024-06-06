#include "obstaculo.h"

obstaculo::obstaculo()
{

}

obstaculo::obstaculo(int x, int y, int w, int h)
{
    this->posx=x;
    this->posy=y;
    this->h=h;
    this->w=w;
}

obstaculo::obstaculo(int x, int y, int w, int h, QString im)
{
    this->posx=x;
    this->posy=y;
    this->h=h;
    this->w=w;
    this->imageName = im;
}

QRectF obstaculo::boundingRect() const
{
    return QRectF(posx,posy,w,h);
}

void obstaculo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(imageName == ":/sprites/puntos_apuntado.png") // si se quiere que la obstaculo tenga algun aspecto en especifio
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
        painter->setBrush(Qt::yellow);
        painter->drawRect(boundingRect());
    }

}
