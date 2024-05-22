#ifndef FARAON_H
#define FARAON_H
#include "Personaje.h"

class faraon : public Personaje
{
public:
    faraon(qreal _x, qreal _y);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void perseguirJugador();
    void evitarProyectil();
};

#endif // FARAON_H
