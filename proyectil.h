#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <QGraphicsItem>
#include <QGraphicsView>

class QTimer;

class Proyectil : public QGraphicsItem
{
public:
    Proyectil(QGraphicsView *view, float velIn,  qreal xIn, qreal yIn, float theta, QGraphicsItem *parent = nullptr); //Es un constructor que puede tomar un puntero a un padre

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    // Reimplementación del evento Keypress
    void keyPressEvent(QKeyEvent *event) override;

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
