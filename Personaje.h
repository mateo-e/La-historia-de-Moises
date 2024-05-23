#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include <QPixmap>

class Personaje:public QObject,
             public QGraphicsPixmapItem //hereda de QObject (para características de objetos de Qt) y de QGraphicsPixmapItem (para objetos gráficos en una escena gráfica de Qt).
{
    Q_OBJECT
protected:
    short int cont=0;
    short int spriteX;
    QPixmap *image;



public:
    short int num_proyectiles;
    short int vida = 100;
    char dir = 'w';
    qreal x;
    qreal y;
    Personaje(qreal _x, qreal _y);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    // Movimiento
    void moveBy(short int dx, short int dy);
    //Simular caminar
    void setSprite();
};
#endif // PERSONAJE_H
