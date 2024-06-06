#ifndef faraon_H
#define faraon_H
#include "Personaje.h"
#include <cstdlib> // Necesario para la función rand()
#include <ctime>   // Necesario para inicializar la semilla
#include <iostream>

class villano : public Personaje
{
public:
    villano(qreal _x, qreal _y);
    QRectF boundingRect() const override;
    bool es_faraon = true;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void setSprite();
    void despl_x();
    bool proy_lanzado = false;
    Proyectil *lanza;
    bool mover = true;
};

#endif // faraon_H
