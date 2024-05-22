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
    Proyectil(QGraphicsView *view, float velIn,  qreal xIn, qreal yIn, float theta, QGraphicsItem *parent = nullptr); //Es un constructor que puede tomar un puntero a un padre

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    // Movimiento
    void moveBy(int dx, int dy);
    void movParabolico(float *dt);

private: //Podrían ser públicas
    qreal posX;
    qreal posY;
    QSize viewRect;
    float velIn, theta, dir;
    qreal xIn, yIn;
};

#endif // PROYECTIL_H
