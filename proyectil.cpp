#include "proyectil.h"

Proyectil::Proyectil(QGraphicsView *view, float velIn,  qreal xIn, qreal yIn, float theta,QGraphicsItem *parent)
    : QGraphicsItem(parent), velIn(velIn), theta(theta), xIn(xIn), yIn(yIn),view(view)
{
    setFlag(QGraphicsItem::ItemIsFocusable); //Inicialización opcional para decir que tiene el foco para eventos del teclado
    dir=1;

    if(view != nullptr)
        aspecto = new QPixmap(":/sprites/piedra.png");
    else
        aspecto = new QPixmap(":/sprites/cetro_faraon.png");

    tiempoTrans = 0;

    posX = xIn;
    posY = yIn;
}

QRectF Proyectil::boundingRect() const
{
    if(view != nullptr)
        return QRectF(posX, posY, 30, 30); // Xoordenadas iniciales del rect (sobre el origen del punto), unidades a la derecha y unidades abajo
    else
        return QRectF(posX, posY, 50, 80);
}

void Proyectil::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(pintar)
    {
        if(view != nullptr)
        {
            painter->drawPixmap(posX,posY,30,30,*aspecto);
            rotacion += 0.02;
        }
        else
        {
            painter->drawPixmap(posX,posY,50,80,*aspecto);
            rotacion -= 0.05;
        }
        setTransformOriginPoint(boundingRect().center()); // se ajusta el eje de giro
        setRotation(rotacion);
    }
}



void Proyectil::moveBy(int dx, int dy)
{
    posX += dx;
    posY += dy;
    setPos(posX, posY);
}

void Proyectil::movParabolico(float *dt)
{
    if(pintar)
    {

        posX = xIn + (velIn*cos(theta) * *dt)*dir;
        posY = yIn - (velIn *sin(theta) * *dt) + (0.5*9.8 * *dt * *dt);

        if(posY>310){
            if(theta > 45 and theta + 12 < 90)
                theta +=12;
            else
                theta +=5;

            theta = -atan((velIn*sin(theta)-9.8 * *dt)/velIn*cos(theta));
            velIn = 0.4 * sqrt(pow(velIn*sin(theta)-9.8 * *dt,2)+pow(velIn*cos(theta),2));
            *dt = 0;
            yIn = posY;
            xIn = posX;
        }



        setPos(posX,posY);
    }
}
