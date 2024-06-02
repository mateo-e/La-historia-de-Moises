#ifndef FARAON_H
#define FARAON_H
#include "Personaje.h"
#include <cstdlib> // Necesario para la función rand()
#include <ctime>   // Necesario para inicializar la semilla
#include <iostream>

class faraon : public Personaje
{
public:
    faraon(qreal _x, qreal _y);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void perseguirJugador();
    void setSprite();
    void despl_x();
    bool proy_lanzado = false;
    Proyectil *lanza;
};

#endif // FARAON_H
