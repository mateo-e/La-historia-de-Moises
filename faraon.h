#ifndef FARAON_H
#define FARAON_H
#include "Personaje.h"

class faraon : public Personaje
{
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:

};

#endif // FARAON_H
