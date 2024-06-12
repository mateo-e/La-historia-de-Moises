#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QObject>
#include <cmath>

class QTimer;

class Proyectil : public QGraphicsItem
{
public:
    Proyectil(QGraphicsView *view, qreal velIn,  qreal xIn, qreal yIn, qreal theta, QGraphicsItem *parent = nullptr); //Es un constructor que puede tomar un puntero a un padre

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    // Movimiento
    void moveBy(int dx, int dy);
    void movParabolico(qreal *dt);
    qreal posX,posY,velIn,tiempoTrans;
    bool pintar = true;

private: //Podrían ser públicas

    QGraphicsView *view;
    QSize viewRect;
    qreal xIn, yIn, rotacion = 0,theta, dir;

    QPixmap *aspecto;
};

#endif // PROYECTIL_H
