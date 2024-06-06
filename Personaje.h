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
    short int spriteX;
    short int num_proyectiles = 3, cont_casas = 0;
    short int vidas;
    char dir = 'd';
    char aspecto = '1';
    qreal x;
    qreal y;
    obstaculo *sombra_apuntado;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    // Movimiento
    void moveBy(short int dx, short int dy);
    //Simular caminar
    void setSprite();
    obstaculo *getSombra_apuntado() const;
    void setSombra_apuntado(obstaculo *newSombra_apuntado);
    qreal posY_in;
    float tiempoTrans = 0;
    void saltar();
    QList<Proyectil *> piedras;
    QFile *dialogue;
};
#endif // PERSONAJE_H
