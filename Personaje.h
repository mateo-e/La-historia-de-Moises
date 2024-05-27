#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include <QPixmap>
#include <pared.h>
#include <proyectil.h>

class Personaje:public QObject,
             public QGraphicsPixmapItem //hereda de QObject (para características de objetos de Qt) y de QGraphicsPixmapItem (para objetos gráficos en una escena gráfica de Qt).
{
    Q_OBJECT

private:
    bool bandera = false;  

protected:
    QPixmap *image;
    short int cont=0;
    short int spriteX;


public:
    short int num_proyectiles = 3;
    short int vidas;
    char dir = 'd';
    qreal x;
    qreal y;
    pared *sombra_apuntado;
    Personaje(qreal _x, qreal _y);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    // Movimiento
    void moveBy(short int dx, short int dy);
    //Simular caminar
    void setSprite();
    pared *getSombra_apuntado() const;
    void setSombra_apuntado(pared *newSombra_apuntado);
    bool getBandera() const;
    void setBandera(bool newBandera);
    QList<Proyectil *> piedras;

};
#endif // PERSONAJE_H
