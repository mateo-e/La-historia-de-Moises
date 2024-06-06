#ifndef OBSTACULO_H
#define OBSTACULO_H
#include <QGraphicsItem>
#include <QPainter>

class obstaculo: public QGraphicsItem
{


public:
    obstaculo();
    obstaculo(int x, int y, int w, int h);
    obstaculo(int x, int y, int w, int h, QString im);

    QString imageName = NULL;
    short int largoTotal = 90,cont = 0, w, h;
    qreal posx, posy;
    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget = nullptr);
};

#endif // OBSTACULO_H
