#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include <QPixmap>
#include <obstaculo.h>
#include <proyectil.h>
#include <QFile>

class Personaje:public QObject,
             public QGraphicsPixmapItem //hereda de QObject (para características de objetos de Qt) y de QGraphicsPixmapItem (para objetos gráficos en una escena gráfica de Qt).
{
    Q_OBJECT 

protected:
    QPixmap *image;
    short int cont=0;

public:
    Personaje(qreal _x, qreal _y);
    Personaje(qreal _x, qreal _y,char _aspecto);
    short int spriteX,num_proyectiles = 3, cont_casas = 0,vidas;
    char dir = 'd',aspecto = '1';
    qreal x , y, posY_in,tiempoTrans = 0;
    obstaculo *sombra_apuntado;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    // Movimiento
    void moveBy(short int dx, short int dy);
    //Simular caminar
    void setSprite();
    void saltar();
    QList<Proyectil *> piedras;
    QFile *dialogue;
};
#endif // PERSONAJE_H
