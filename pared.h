#ifndef PARED_H
#define PARED_H
#include <QGraphicsItem>
#include <QPainter>

class pared: public QGraphicsItem
{


public:
    pared();
    pared(int x, int y, int w, int h);
    pared(int x, int y, int w, int h, QString im);

    QString imageName = NULL;
    short int largoTotal = 90,cont = 0,posx, posy, w, h;

    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget = nullptr);
};

#endif // PARED_H
